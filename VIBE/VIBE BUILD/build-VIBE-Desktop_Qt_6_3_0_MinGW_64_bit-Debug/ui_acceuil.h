/********************************************************************************
** Form generated from reading UI file 'acceuil.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCEUIL_H
#define UI_ACCEUIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_acceuil
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *acceuil)
    {
        if (acceuil->objectName().isEmpty())
            acceuil->setObjectName(QString::fromUtf8("acceuil"));
        acceuil->resize(1242, 719);
        acceuil->setToolButtonStyle(Qt::ToolButtonIconOnly);
        acceuil->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(acceuil);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        acceuil->setCentralWidget(centralwidget);
        menubar = new QMenuBar(acceuil);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1242, 25));
        acceuil->setMenuBar(menubar);

        retranslateUi(acceuil);

        QMetaObject::connectSlotsByName(acceuil);
    } // setupUi

    void retranslateUi(QMainWindow *acceuil)
    {
        acceuil->setWindowTitle(QCoreApplication::translate("acceuil", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class acceuil: public Ui_acceuil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCEUIL_H
