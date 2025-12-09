#include "qr_activite.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <QDateTime>
#include <QCoreApplication>
#include <QUrl>
#include <QRegularExpression>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

QString QRCodeGenerator::getQRContent(const Activite &activite)
{
    // Create a URL format for maximum scannability
    // This format is recognized by ALL QR code readers
    
    QString content;
    
    // Using a custom scheme that can be registered as a deep link
    content = QString("inspira://activite/%1").arg(activite.id_activite);
    content += QString("?nom=%1").arg(QString(QUrl::toPercentEncoding(activite.nom)));
    content += QString("&telephone=%1").arg(QString(QUrl::toPercentEncoding(activite.telephone)));
    content += QString("&type=%1").arg(QString(QUrl::toPercentEncoding(activite.type)));
    content += QString("&duree=%1").arg(activite.duree);
    content += QString("&capacite=%1").arg(activite.capacite);
    
    qDebug() << "[QR] Generated URL content:" << content;
    return content;
}

QString QRCodeGenerator::getQRCodesDirectory()
{
    QString appDir = QCoreApplication::applicationDirPath();
    return appDir + "/qr_codes";
}

bool QRCodeGenerator::ensureQRCodesDirectoryExists()
{
    QString qrDir = getQRCodesDirectory();
    QDir dir;
    
    if (!dir.exists(qrDir)) {
        if (dir.mkpath(qrDir)) {
            qDebug() << "[QR] Created QR codes directory:" << qrDir;
            return true;
        } else {
            qWarning() << "[QR] Failed to create QR codes directory:" << qrDir;
            return false;
        }
    }
    
    return true;
}

QString QRCodeGenerator::generateQRFileName(const Activite &activite)
{
    // Clean the title to make it filename-safe
    QString safeTitle = activite.nom;
    safeTitle.replace(QRegularExpression("[^a-zA-Z0-9]"), "_");
    if (safeTitle.length() > 30) {
        safeTitle = safeTitle.left(30);
    }
    
    return QString("QR_Activite_%1_%2.png").arg(activite.id_activite).arg(safeTitle);
}

QImage QRCodeGenerator::downloadQRFromAPI(const QString &text, int size)
{
    qDebug() << "[QR] Downloading QR code from API for text:" << text.left(50) << "...";
    
    // Using api.qrserver.com - a free, reliable QR code API
    // URL format: https://api.qrserver.com/v1/create-qr-code/?size=400x400&data=YOUR_TEXT
    
    QString encodedText = QString(QUrl::toPercentEncoding(text));
    QString apiUrl = QString("https://api.qrserver.com/v1/create-qr-code/?size=%1x%1&data=%2")
                        .arg(size)
                        .arg(encodedText);
    
    qDebug() << "[QR] API URL:" << apiUrl;
    
    // Create network manager
    QNetworkAccessManager manager;
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::UserAgentHeader, "InspiraStudio/1.0");
    
    // Send GET request
    QNetworkReply *reply = manager.get(request);
    
    // Wait for response
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    
    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "[QR] API request failed:" << reply->errorString();
        reply->deleteLater();
        return QImage(); // Return null image
    }
    
    // Read image data
    QByteArray imageData = reply->readAll();
    reply->deleteLater();
    
    // Convert to QImage
    QImage qrImage;
    if (!qrImage.loadFromData(imageData)) {
        qWarning() << "[QR] Failed to load image from API response";
        return QImage();
    }
    
    qDebug() << "[QR] Successfully downloaded QR code from API. Size:" << qrImage.size();
    return qrImage;
}

QImage QRCodeGenerator::createFallbackImage(const QString &text, int size)
{
    qDebug() << "[QR] Creating fallback image (API unavailable)";
    
    QImage image(size, size, QImage::Format_RGB32);
    image.fill(Qt::white);
    
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw border
    painter.setPen(QPen(Qt::black, 3));
    painter.drawRect(10, 10, size - 20, size - 20);
    
    // Draw warning icon (triangle with exclamation)
    painter.setBrush(QColor(255, 165, 0)); // Orange
    QPolygon triangle;
    triangle << QPoint(size/2, size/4) 
             << QPoint(size/4, size/2) 
             << QPoint(3*size/4, size/2);
    painter.drawPolygon(triangle);
    
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(QRect(size/2 - 10, size/4 + 20, 20, 40), Qt::AlignCenter, "!");
    
    // Draw message
    painter.setFont(QFont("Arial", 10));
    QString message = "QR Code Generation\nRequires Internet\n\nActivite Info:\n" + text.left(100);
    painter.drawText(QRect(20, size/2 + 40, size - 40, size/2 - 60), 
                     Qt::AlignCenter | Qt::TextWordWrap, message);
    
    painter.end();
    
    return image;
}

QImage QRCodeGenerator::generateQRCode(const Activite &activite, const QString &outputPath)
{
    QString qrText = getQRContent(activite);
    
    // Try to download from API
    QImage qrImage = downloadQRFromAPI(qrText, 400);
    
    // If API fails, create fallback image
    if (qrImage.isNull()) {
        qWarning() << "[QR] API download failed, using fallback image";
        qrImage = createFallbackImage(qrText, 400);
    }
    
    return qrImage;
}

QString QRCodeGenerator::generateAndSaveQRCode(const Activite &activite, const QString &outputPath)
{
    // Ensure QR codes directory exists
    if (!ensureQRCodesDirectoryExists()) {
        qWarning() << "[QR] Cannot create QR codes directory";
        return QString();
    }
    
    // Generate QR code image
    QImage qrImage = generateQRCode(activite, outputPath);
    
    if (qrImage.isNull()) {
        qWarning() << "[QR] Failed to generate QR code image";
        return QString();
    }
    
    // Determine output file path
    QString filePath;
    if (outputPath.isEmpty()) {
        QString qrDir = getQRCodesDirectory();
        QString fileName = generateQRFileName(activite);
        filePath = qrDir + "/" + fileName;
    } else {
        filePath = outputPath;
    }
    
    // Save image
    if (qrImage.save(filePath, "PNG")) {
        qDebug() << "[QR] QR code saved successfully to:" << filePath;
        return filePath;
    } else {
        qWarning() << "[QR] Failed to save QR code to:" << filePath;
        return QString();
    }
}
