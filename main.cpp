#include "mainwindow.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    QApplication::setApplicationName("ISR");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("DuarteCorporation");
    QApplication::setOrganizationDomain("www.duartecorporation.com");

    Logger::initialize();
    Logger::setOutputFilePath("C:/Users/carlo/OneDrive/Desktop/ISRlog.txt");

    MainWindow w;
    w.show();

    int ret = a.exec();
    Logger::finalize();
    return ret;
}
