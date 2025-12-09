#include "activite.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Application starting...";

    try {
        MainWindow window;
        qDebug() << "MainWindow created successfully";

        window.show();
        qDebug() << "Window shown";

        return app.exec();
    }
    catch (const std::exception& e) {
        qDebug() << "Exception caught:" << e.what();
        QMessageBox::critical(nullptr, "Error", QString("Exception: %1").arg(e.what()));
        return -1;
    }
    catch (...) {
        qDebug() << "Unknown exception caught";
        QMessageBox::critical(nullptr, "Error", "Unknown exception occurred");
        return -1;
    }
}
