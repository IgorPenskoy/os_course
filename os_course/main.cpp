#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    FILE *f = fopen("exec_log.txt", "w");
    fclose(f);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QProcess execmon;
    if (getuid() != 0) {
        QMessageBox msg_box;
        msg_box.setText("Это приложение должно быть запущено с правами суперпользователя для обеспечения полной функциональности");
        msg_box.exec();
    }
    else {
        QProcess::execute("insmod ../execmon/execmon.ko");
        execmon.start("../execmon/execmon");
    }
    a.exec();
    if (getuid() == 0) {
        execmon.kill();
        QProcess::execute("rmmod execmon");
    }
    return 0;
}
