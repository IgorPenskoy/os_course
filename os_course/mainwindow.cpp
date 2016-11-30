#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "update_functions.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->update_info();
    this->update_process_table();
    this->update_journal();
    QTimer *info_timer = new QTimer;
    connect(info_timer, SIGNAL(timeout()), this, SLOT(update_info()));
    info_timer->start(2000);
    connect(ui->kill_process_pushbutton, SIGNAL(clicked()), this, SLOT(kill_process()));
    QTimer *process_table_timer = new QTimer;
    connect(process_table_timer, SIGNAL(timeout()), this, SLOT(update_process_table()));
    process_table_timer->start(4000);
    QTimer *journal_timer = new QTimer;
    connect(journal_timer, SIGNAL(timeout()), this, SLOT(update_journal()));
    journal_timer->start(5000);
}

void MainWindow::update_info() {
    ui->host_name_label->setText("Имя компьютера: " + get_hostname());
    ui->user_name_label->setText("Имя пользователя: " + get_user_name());
    ui->uptime_label->setText("Время непрерывной работы: " + get_uptime());
    ui->cpu_model_label->setText("Модель центрального процессора: " + get_cpu_model());
    ui->cpu_frequency_label->setText("Частота центрального процессора: " + get_cpu_frequency() + " MHz");
    ui->cpu_load_progressbar->setValue(get_cpu_load(0.3));
    ui->total_memory_label->setText("Доступная оперативная память: " + get_available_memory());
    ui->busy_memory_lable->setText("Используемая оперативная память: " + get_busy_memory());
    ui->busy_memory_progressbar->setValue(get_memory_percentage());
}

void MainWindow::update_process_table() {
    ui->process_table_tablewidget->setColumnCount(2);
    ui->process_table_tablewidget->setRowCount(0);
    QStringList list;
    list << "Name" << "PID";
    ui->process_table_tablewidget->setHorizontalHeaderLabels(list);
    QDir * dir = new QDir("/proc");
    list = dir->entryList(QStringList("*"), QDir::AllDirs);
    foreach(QString str, list) {
        if(str.toInt()) {
            std::ifstream stream;
            stream.open("/proc/" + str.toUtf8() + "/comm");
            std::string s;
            getline(stream, s);
            int lastRow = ui->process_table_tablewidget->rowCount();
            ui->process_table_tablewidget->insertRow(lastRow);
            ui->process_table_tablewidget->setColumnWidth(0, 150);
            ui->process_table_tablewidget->setItem(lastRow, 0, new QTableWidgetItem(QString::fromStdString(s)));
            ui->process_table_tablewidget->setItem(lastRow, 1, new QTableWidgetItem(str));
        }
    }
}

void MainWindow::kill_process() {
    QList <QTableWidgetItem *> list = ui->process_table_tablewidget->selectedItems();
    if (list.length() > 0) {
        QTableWidgetItem *item = list.value(1);
        QString str = item->text();
        QProcess::execute("kill", QStringList() << str);
        update();
    }
}

void MainWindow::update_journal() {
    ui->journal_content->setText(QString::fromStdString(file_read("exec_log.txt")));
    QTextCursor c = ui->journal_content->textCursor();
    c.movePosition(QTextCursor::End);
    ui->journal_content->setTextCursor(c);
}

MainWindow::~MainWindow() {
    delete ui;
}
