/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabs;
    QWidget *info_tab;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *host_name_label;
    QLabel *user_name_label;
    QLabel *uptime_label;
    QLabel *cpu_model_label;
    QLabel *cpu_frequency_label;
    QHBoxLayout *horizontalLayout;
    QLabel *cpu_load_label;
    QProgressBar *cpu_load_progressbar;
    QLabel *total_memory_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *busy_memory_lable;
    QProgressBar *busy_memory_progressbar;
    QWidget *process_table_tab;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *process_table_tablewidget;
    QPushButton *kill_process_pushbutton;
    QWidget *journal_exe;
    QGridLayout *gridLayout_4;
    QTextEdit *journal_content;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(509, 352);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabs = new QTabWidget(centralWidget);
        tabs->setObjectName(QStringLiteral("tabs"));
        info_tab = new QWidget();
        info_tab->setObjectName(QStringLiteral("info_tab"));
        gridLayout_2 = new QGridLayout(info_tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        host_name_label = new QLabel(info_tab);
        host_name_label->setObjectName(QStringLiteral("host_name_label"));

        verticalLayout->addWidget(host_name_label);

        user_name_label = new QLabel(info_tab);
        user_name_label->setObjectName(QStringLiteral("user_name_label"));

        verticalLayout->addWidget(user_name_label);

        uptime_label = new QLabel(info_tab);
        uptime_label->setObjectName(QStringLiteral("uptime_label"));

        verticalLayout->addWidget(uptime_label);

        cpu_model_label = new QLabel(info_tab);
        cpu_model_label->setObjectName(QStringLiteral("cpu_model_label"));

        verticalLayout->addWidget(cpu_model_label);

        cpu_frequency_label = new QLabel(info_tab);
        cpu_frequency_label->setObjectName(QStringLiteral("cpu_frequency_label"));

        verticalLayout->addWidget(cpu_frequency_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cpu_load_label = new QLabel(info_tab);
        cpu_load_label->setObjectName(QStringLiteral("cpu_load_label"));

        horizontalLayout->addWidget(cpu_load_label);

        cpu_load_progressbar = new QProgressBar(info_tab);
        cpu_load_progressbar->setObjectName(QStringLiteral("cpu_load_progressbar"));
        cpu_load_progressbar->setValue(0);

        horizontalLayout->addWidget(cpu_load_progressbar);


        verticalLayout->addLayout(horizontalLayout);

        total_memory_label = new QLabel(info_tab);
        total_memory_label->setObjectName(QStringLiteral("total_memory_label"));

        verticalLayout->addWidget(total_memory_label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        busy_memory_lable = new QLabel(info_tab);
        busy_memory_lable->setObjectName(QStringLiteral("busy_memory_lable"));

        horizontalLayout_2->addWidget(busy_memory_lable);

        busy_memory_progressbar = new QProgressBar(info_tab);
        busy_memory_progressbar->setObjectName(QStringLiteral("busy_memory_progressbar"));
        busy_memory_progressbar->setValue(0);

        horizontalLayout_2->addWidget(busy_memory_progressbar);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        tabs->addTab(info_tab, QString());
        process_table_tab = new QWidget();
        process_table_tab->setObjectName(QStringLiteral("process_table_tab"));
        gridLayout_3 = new QGridLayout(process_table_tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        process_table_tablewidget = new QTableWidget(process_table_tab);
        process_table_tablewidget->setObjectName(QStringLiteral("process_table_tablewidget"));
        process_table_tablewidget->setSelectionMode(QAbstractItemView::SingleSelection);
        process_table_tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_2->addWidget(process_table_tablewidget);

        kill_process_pushbutton = new QPushButton(process_table_tab);
        kill_process_pushbutton->setObjectName(QStringLiteral("kill_process_pushbutton"));

        verticalLayout_2->addWidget(kill_process_pushbutton);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabs->addTab(process_table_tab, QString());
        journal_exe = new QWidget();
        journal_exe->setObjectName(QStringLiteral("journal_exe"));
        gridLayout_4 = new QGridLayout(journal_exe);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        journal_content = new QTextEdit(journal_exe);
        journal_content->setObjectName(QStringLiteral("journal_content"));
        journal_content->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(journal_content, 0, 0, 1, 1);

        tabs->addTab(journal_exe, QString());

        gridLayout->addWidget(tabs, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 509, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\321\213\320\271 \320\274\320\276\320\275\320\270\321\202\320\276\321\200 Linux. v 0.0.1", 0));
        host_name_label->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\260:", 0));
        user_name_label->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", 0));
        uptime_label->setText(QApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\265\320\277\321\200\320\265\321\200\321\213\320\262\320\275\320\276\320\271 \321\200\320\260\320\261\320\276\321\202\321\213:", 0));
        cpu_model_label->setText(QApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214 \321\206\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260:", 0));
        cpu_frequency_label->setText(QApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \321\206\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260:", 0));
        cpu_load_label->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260:", 0));
        total_memory_label->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\320\260\321\217 \320\276\320\277\320\265\321\200\320\260\321\202\320\270\320\262\320\275\320\260\321\217 \320\277\320\260\320\274\321\217\321\202\321\214:", 0));
        busy_memory_lable->setText(QApplication::translate("MainWindow", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\320\274\320\260\321\217 \320\276\320\277\320\265\321\200\320\260\321\202\320\270\320\262\320\275\320\260\321\217 \320\277\320\260\320\274\321\217\321\202\321\214:", 0));
        tabs->setTabText(tabs->indexOf(info_tab), QApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\201\320\270\321\201\321\202\320\265\320\274\320\265", 0));
        kill_process_pushbutton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201", 0));
        tabs->setTabText(tabs->indexOf(process_table_tab), QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201\321\213", 0));
        tabs->setTabText(tabs->indexOf(journal_exe), QApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273 \320\267\320\260\320\277\321\203\321\211\320\265\320\275\320\275\321\213\321\205 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
