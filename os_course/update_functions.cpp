#include "update_functions.h"

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
    QProcess::execute("sleep",QStringList() << QString::number(dt));
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
    std::string str;
    QString e("");
    std::ifstream stream("/proc/meminfo");
    stream >> str;
    stream >> str;
    int num = atoi(str.c_str());
    for (int i = 0; i < 6; i++) {
        stream >> str;
    }
    int free = atoi(str.c_str());
    num -= free;
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

int get_memory_percentage() {
    std::string str;
    QString e("");
    std::ifstream stream("/proc/meminfo");
    stream >> str;
    stream >> str;
    int num = atoi(str.c_str());
    for (int i = 0; i < 6; i++) {
        stream >> str;
    }
    stream.close();
    int free = atoi(str.c_str());
    return 100 - (int)((float)free / (float)num * 100);
}

std::string file_read(const char *file_name) {
    std::string str;
    std::ifstream ifs(file_name);
    ifs >> std::noskipws;
    std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(str));
    return str;
}
