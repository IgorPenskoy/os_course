#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QProcess>
#include <QDir>
#include <QScrollBar>

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <stdio.h>

static const int info_update_gap = 1000;
static const int process_table_update_gap = 4010;
static const int journal_update_gap = 5020;
static const int cpu_stats_gap = 300;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void update_info();
    void update_process_table();
    void update_journal();
    void kill_process();
};

#endif // MAINWINDOW_H
