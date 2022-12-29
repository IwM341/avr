/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *minT;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QPushButton *set;
    QTextBrowser *debug;
    QLabel *label_2;
    QDoubleSpinBox *maxT;
    QLineEdit *duration;
    QLineEdit *interval;
    QSpacerItem *horizontalSpacer;
    QPushButton *connect;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        minT = new QDoubleSpinBox(centralwidget);
        minT->setObjectName(QString::fromUtf8("minT"));
        minT->setDecimals(1);
        minT->setMinimum(10.000000000000000);
        minT->setMaximum(99.900000000000006);
        minT->setSingleStep(0.200000000000000);

        gridLayout_2->addWidget(minT, 4, 3, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(12);
        label_3->setFont(font);

        gridLayout_2->addWidget(label_3, 3, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 1, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 4, 2, 1, 1);

        set = new QPushButton(centralwidget);
        set->setObjectName(QString::fromUtf8("set"));

        gridLayout_2->addWidget(set, 5, 2, 1, 2);

        debug = new QTextBrowser(centralwidget);
        debug->setObjectName(QString::fromUtf8("debug"));

        gridLayout_2->addWidget(debug, 6, 2, 1, 4);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 2, 2, 1, 1);

        maxT = new QDoubleSpinBox(centralwidget);
        maxT->setObjectName(QString::fromUtf8("maxT"));
        maxT->setDecimals(1);
        maxT->setMinimum(10.000000000000000);
        maxT->setMaximum(99.900000000000006);
        maxT->setSingleStep(0.200000000000000);

        gridLayout_2->addWidget(maxT, 3, 3, 1, 1);

        duration = new QLineEdit(centralwidget);
        duration->setObjectName(QString::fromUtf8("duration"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(duration->sizePolicy().hasHeightForWidth());
        duration->setSizePolicy(sizePolicy);
        duration->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(duration, 2, 3, 1, 1);

        interval = new QLineEdit(centralwidget);
        interval->setObjectName(QString::fromUtf8("interval"));
        sizePolicy.setHeightForWidth(interval->sizePolicy().hasHeightForWidth());
        interval->setSizePolicy(sizePolicy);
        interval->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(interval, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 5, 1, 1);

        connect = new QPushButton(centralwidget);
        connect->setObjectName(QString::fromUtf8("connect"));

        gridLayout_2->addWidget(connect, 0, 1, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        label->raise();
        maxT->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        minT->raise();
        debug->raise();
        set->raise();
        duration->raise();
        connect->raise();
        interval->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(connect, interval);
        QWidget::setTabOrder(interval, duration);
        QWidget::setTabOrder(duration, maxT);
        QWidget::setTabOrder(maxT, minT);
        QWidget::setTabOrder(minT, set);
        QWidget::setTabOrder(set, debug);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Max Temperature", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Water Interval", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Min Temperature", nullptr));
        set->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Duration", nullptr));
        duration->setInputMask(QCoreApplication::translate("MainWindow", "99m:99s", nullptr));
        duration->setText(QCoreApplication::translate("MainWindow", "59m:59s", nullptr));
        interval->setInputMask(QCoreApplication::translate("MainWindow", "99\\h:99m:99s", nullptr));
        interval->setText(QCoreApplication::translate("MainWindow", "99h:59m:59s", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
