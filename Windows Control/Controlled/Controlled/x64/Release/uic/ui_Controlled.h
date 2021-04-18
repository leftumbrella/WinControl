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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlledClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ControlledClass)
    {
        if (ControlledClass->objectName().isEmpty())
            ControlledClass->setObjectName(QString::fromUtf8("ControlledClass"));
        ControlledClass->resize(600, 400);
        menuBar = new QMenuBar(ControlledClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ControlledClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ControlledClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ControlledClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ControlledClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ControlledClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ControlledClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ControlledClass->setStatusBar(statusBar);

        retranslateUi(ControlledClass);

        QMetaObject::connectSlotsByName(ControlledClass);
    } // setupUi

    void retranslateUi(QMainWindow *ControlledClass)
    {
        ControlledClass->setWindowTitle(QCoreApplication::translate("ControlledClass", "Controlled", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlledClass: public Ui_ControlledClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLED_H
