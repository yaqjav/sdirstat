#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QApplication::setWindowIcon(QIcon(":/assets/sdirstat.png"));
    return QApplication::exec();
}
