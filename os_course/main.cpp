#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QStyle * style = QStyleFactory::create("Cleanlooks");
    a.setStyle(style);
    QProcess execmon;
    execmon.start("../execmon/execmon");
    a.exec();
    execmon.kill();
    return 0;
}
