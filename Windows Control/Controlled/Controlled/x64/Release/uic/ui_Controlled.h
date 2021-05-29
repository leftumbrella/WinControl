/********************************************************************************
** Form generated from reading UI file 'Controlled.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLLED_H
#define UI_CONTROLLED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlledClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *WG_main;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QLabel *LB_volume_now;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *SB_volume;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_volume_set;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_volume_less;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_volume_add;

    void setupUi(QMainWindow *ControlledClass)
    {
        if (ControlledClass->objectName().isEmpty())
            ControlledClass->setObjectName(QString::fromUtf8("ControlledClass"));
        ControlledClass->resize(1128, 840);
        centralWidget = new QWidget(ControlledClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        WG_main = new QWidget(centralWidget);
        WG_main->setObjectName(QString::fromUtf8("WG_main"));
        gridLayout_2 = new QGridLayout(WG_main);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_3 = new QWidget(WG_main);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        LB_volume_now = new QLabel(widget_3);
        LB_volume_now->setObjectName(QString::fromUtf8("LB_volume_now"));
        LB_volume_now->setStyleSheet(QString::fromUtf8(""));
        LB_volume_now->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LB_volume_now);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        SB_volume = new QSpinBox(widget_2);
        SB_volume->setObjectName(QString::fromUtf8("SB_volume"));

        horizontalLayout_2->addWidget(SB_volume);

        horizontalSpacer_2 = new QSpacerItem(930, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btn_volume_set = new QPushButton(widget_2);
        btn_volume_set->setObjectName(QString::fromUtf8("btn_volume_set"));

        horizontalLayout_2->addWidget(btn_volume_set);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_volume_less = new QPushButton(widget);
        btn_volume_less->setObjectName(QString::fromUtf8("btn_volume_less"));

        horizontalLayout->addWidget(btn_volume_less);

        horizontalSpacer = new QSpacerItem(891, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_volume_add = new QPushButton(widget);
        btn_volume_add->setObjectName(QString::fromUtf8("btn_volume_add"));

        horizontalLayout->addWidget(btn_volume_add);


        verticalLayout->addWidget(widget);


        gridLayout_2->addWidget(widget_3, 0, 0, 1, 1);


        gridLayout->addWidget(WG_main, 0, 0, 1, 1);

        ControlledClass->setCentralWidget(centralWidget);

        retranslateUi(ControlledClass);

        QMetaObject::connectSlotsByName(ControlledClass);
    } // setupUi

    void retranslateUi(QMainWindow *ControlledClass)
    {
        ControlledClass->setWindowTitle(QCoreApplication::translate("ControlledClass", "Controlled", nullptr));
        LB_volume_now->setText(QCoreApplication::translate("ControlledClass", "0", nullptr));
        btn_volume_set->setText(QCoreApplication::translate("ControlledClass", "\350\256\276\347\275\256\351\237\263\351\207\217", nullptr));
        btn_volume_less->setText(QCoreApplication::translate("ControlledClass", "\351\237\263\351\207\217-", nullptr));
        btn_volume_add->setText(QCoreApplication::translate("ControlledClass", "\351\237\263\351\207\217+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlledClass: public Ui_ControlledClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLED_H
