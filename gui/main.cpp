#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Dominik Kapusta");
    QCoreApplication::setOrganizationDomain("kapusta.cc");
    QCoreApplication::setApplicationName("FontToBytes");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
