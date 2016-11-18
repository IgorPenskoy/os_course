#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->update_info();
    this->update_process_table();
    QTimer *info_timer = new QTimer;
    connect(info_timer, SIGNAL(timeout()), this, SLOT(update_info()));
    info_timer->start(2000);
    connect(ui->kill_process_pushbutton, SIGNAL(clicked()), this, SLOT(kill_process()));
    QTimer *process_table_timer = new QTimer;
    connect(process_table_timer, SIGNAL(timeout()), this, SLOT(update_process_table()));
    process_table_timer->start(4000);
}

std::vector <float> MainWindow::read_cpu_stats() {
    std::vector <float> ret;
    std::ifstream stat_file("/proc/stat");
    if (!stat_file.is_open()) {
        std::cout << "Unable to open /proc/stat" << std::endl;
        return ret;
    }
    int val;
    std::string tmp;
    stat_file >> tmp;
    for (int i = 0; i < 4; ++i) {
        stat_file >> val;
        ret.push_back(val);
    }
    stat_file.close();
    return ret;
}

int MainWindow::get_cpu_load(double dt) {
    std::vector <float> stats1 = read_cpu_stats();
    QProcess::execute("sleep", QStringList() << QString::number(dt));
    std::vector <float> stats2 = read_cpu_stats();
    int size1 = stats1.size();
    int size2 = stats2.size();
    if (!size1 || !size2 || size1 != size2)
        return 2;
    for (int i = 0; i < size1; ++i)
        stats2[i] -= stats1[i];
    int sum = 1;
    for (int i = 0; i < size1; ++i)
        sum += stats2[i];
    int load = 100 - (stats2[size2 - 1] * 100 / sum);
    return load;
}

void MainWindow::update_info() {
    std::ifstream stream("/proc/sys/kernel/hostname");
    std::string str;
    getline(stream, str);
    ui->host_name_label->setText("Имя компьютера: " + QString::fromStdString(str));
    uid_t uid = geteuid();
    passwd *pw = getpwuid(uid);
    ui->user_name_label->setText("Имя пользователя: " + QString::fromUtf8(pw->pw_name));
    struct sysinfo sys_info;
    sysinfo(&sys_info);
    long up = sys_info.uptime;
    int hour = up/60/60;
    int min = (up - hour*60*60) / 60;
    int sec =  ((up - hour*60*60) - min*60);
    QString e = QString::number(hour) +  QString(" h. ") + QString::number(min) + QString(" m. ")
                + QString::number(sec) + QString(" s.");
    ui->uptime_label->setText("Время непрерывной работы: " + e);
    stream.close();
    stream.open("/proc/cpuinfo");
    for(int i = 0; i < 16; i++) stream >> str;
    getline(stream, str);
    ui->cpu_model_label->setText("Модель центрального процессора: " + QString::fromStdString(str));
    for(int i = 0; i< 7; i++)  stream >> str;
    ui->cpu_frequency_label->setText("Частота центрального процессора: " + QString::fromStdString(str) + " MHz");
    ui->cpu_load_progressbar->setValue(get_cpu_load(0.3));
    stream.close();
    stream.open("/proc/meminfo");
    stream >> str;
    stream >> str;
    int num = atoi(str.c_str());
    int percent = num / 100;
    int gb = (num / 1024) / 1024;
    int mb = (num-gb*1024*1024) /1024;
    int kb = (num - (gb*1024*1024+mb*1024));
    if (gb > 0)
       e = QString::number(gb) + QString(" Gb ");
    else
       e = QString("");
    if (mb > 0)
       e += QString::number(mb) + QString(" Mb ");
    if (kb > 0)
       e += QString::number(kb) + QString(" Kb ");
    ui->total_memory_label->setText("Доступная оперативная память: " + e);
    int free = 0;
    for (int i = 0; i < 3; i++) {
        stream >> str;
        stream >> str;
        stream >> str;
        free += atoi(str.c_str());
    }
    num -= free;
    gb = num / 1024 / 1024;
    mb = (num - gb*1024*1024) / 1024;
    kb = (num - ((mb*1024) + (gb * 1024 * 1024)));
    if (gb > 0)
       e = QString::number(gb) + QString(" Gb ");
    else
       e = QString("");
    if (mb > 0)
       e += QString::number(mb) + QString(" Mb ");
    if (kb > 0)
       e += QString::number(kb) + QString(" Kb ");
    ui->busy_memory_lable->setText("Используемая оперативная память: " + e);
    percent = num / percent;
    ui->busy_memory_progressbar->setValue(percent);
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
            QString icon = "/usr/share/icons/hicolor/32x32/apps/" + QString::fromStdString(s) + ".png";
            QFile file(icon);
            ui->process_table_tablewidget->insertRow(lastRow);
            ui->process_table_tablewidget->setColumnWidth(0, 150);

            if(!file.exists())
                icon = "binary.png";
            ui->process_table_tablewidget->setItem(lastRow, 0, new QTableWidgetItem(QPixmap(icon), QString::fromStdString(s)));
            ui->process_table_tablewidget->setItem(lastRow, 1, new QTableWidgetItem(str));
        }
    }
}

void MainWindow::kill_process() {
    QList <QTableWidgetItem *> list = ui->process_table_tablewidget->selectedItems();
    if (list.length() > 0) {
        QTableWidgetItem *item = list.value(0);
        QString str = item->text();
        QProcess::execute("kill", QStringList() << str);
        update();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
