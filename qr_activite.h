#ifndef QR_ACTIVITE_H
#define QR_ACTIVITE_H

#include <QString>
#include <QImage>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include "activite.h"

/**
 * @brief QR Code Generator for Activites using online API
 * 
 * This class generates REAL scannable QR codes using an online API
 * and saves them as PNG images in the qr_codes/ folder.
 */
class QRCodeGenerator
{
public:
    /**
     * @brief Generate QR code for an activite using online API
     * @param activite The activite to generate QR code for
     * @param outputPath Optional custom output path (if empty, uses default qr_codes/ folder)
     * @return QImage containing the QR code, or null image if failed
     */
    static QImage generateQRCode(const Activite &activite, const QString &outputPath = QString());
    
    /**
     * @brief Generate and save QR code to file
     * @param activite The activite to generate QR code for
     * @param outputPath Optional custom output path
     * @return File path of saved QR code, or empty string if failed
     */
    static QString generateAndSaveQRCode(const Activite &activite, const QString &outputPath = QString());
    
    /**
     * @brief Get QR code content text for an activite
     * @param activite The activite to encode
     * @return Formatted text content for QR code
     */
    static QString getQRContent(const Activite &activite);
    
    /**
     * @brief Get default QR codes directory path
     * @return Path to qr_codes/ folder
     */
    static QString getQRCodesDirectory();
    
    /**
     * @brief Ensure QR codes directory exists
     * @return true if directory exists or was created successfully
     */
    static bool ensureQRCodesDirectoryExists();
    
    /**
     * @brief Generate QR code file name for an activite
     * @param activite The activite
     * @return File name like "QR_Activite_123.png"
     */
    static QString generateQRFileName(const Activite &activite);

private:
    /**
     * @brief Download real QR code from online API
     * @param text Text to encode
     * @param size QR code size in pixels
     * @return QImage containing the real scannable QR code
     */
    static QImage downloadQRFromAPI(const QString &text, int size = 400);
    
    /**
     * @brief Create fallback QR code image if API fails
     * @param text Text to encode
     * @param size QR code size in pixels
     * @return QImage containing basic info image
     */
    static QImage createFallbackImage(const QString &text, int size = 400);
};

#endif // QR_ACTIVITE_H
