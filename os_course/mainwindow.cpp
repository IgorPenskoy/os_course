#include "mainwindow.h"
#include "ui_mainwindow.h"

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

std::vector <float> read_cpu_stats() {
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

int get_cpu_load(double dt) {
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

QString get_hostname() {
    std::ifstream stream("/proc/sys/kernel/hostname");
    std::string str;
    getline(stream, str);
    stream.close();
    return QString::fromStdString(str);
}

QString get_user_name() {
    uid_t uid = geteuid();
    passwd *pw = getpwuid(uid);
    return QString::fromUtf8(pw->pw_name);
}

QString get_uptime() {
    struct sysinfo sys_info;
    sysinfo(&sys_info);
    long up = sys_info.uptime;
    int hour = up / 60 / 60;
    int min = (up - hour * 60 * 60) / 60;
    int sec =  ((up - hour * 60 * 60) - min * 60);
    return QString::number(hour) +  QString(" ч. ") + QString::number(min) + QString(" м. ")
                + QString::number(sec) + QString(" с.");
}

QString get_cpu_model() {
    std::ifstream stream("/proc/cpuinfo");
    std::string str;
    for(int i = 0; i < 16; i++)
        stream >> str;
    getline(stream, str);
    stream.close();
    return QString::fromStdString(str);
}

QString get_cpu_frequency() {
    std::ifstream stream("/proc/cpuinfo");
    std::string str;
    for(int i = 0; i < 31; i++)
        stream >> str;
    getline(stream, str);
    stream.close();
    return QString::fromStdString(str);
}

QString get_available_memory() {
    std::string str;
    QString e("");
    std::ifstream stream("/proc/meminfo");
    stream >> str;
    stream >> str;
    int num = atoi(str.c_str());
    int gb = (num / 1024) / 1024;
    int mb = (num - gb * 1024 * 1024) / 1024;
    int kb = (num - (gb * 1024 * 1024 + mb * 1024));
    if (gb > 0)
       e = QString::number(gb) + QString(" Gb ");
    if (mb > 0)
       e += QString::number(mb) + QString(" Mb ");
    if (kb > 0)
       e += QString::number(kb) + QString(" Kb ");
    stream.close();
    return e;
}

QString get_busy_memory() {
    return QString("");
}

int get_memory_percentage() {
    return 0;
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
    //    int free = 0;
    //    for (int i = 0; i < 3; i++) {
    //        stream >> str;
    //        stream >> str;
    //        stream >> str;
    //        free += atoi(str.c_str());
    //    }
    //    num -= free;
    //    gb = num / 1024 / 1024;
    //    mb = (num - gb*1024*1024) / 1024;
    //    kb = (num - ((mb*1024) + (gb * 1024 * 1024)));
    //    if (gb > 0)
    //       e = QString::number(gb) + QString(" Gb ");
    //    else
    //       e = QString("");
    //    if (mb > 0)
    //       e += QString::number(mb) + QString(" Mb ");
    //    if (kb > 0)
    //       e += QString::number(kb) + QString(" Kb ");
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

void MainWindow::update_journal() {
    ui->journal_content->setText(QString("TEST STRING\n"));
}

MainWindow::~MainWindow() {
    delete ui;
}
