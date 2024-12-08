/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nom;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *mdp;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *connexion;
    QPushButton *quitter;
    QWidget *widget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1125, 708);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(590, 150, 361, 381));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 9pt \"Sitka\";"));

        horizontalLayout->addWidget(label);

        nom = new QLineEdit(groupBox);
        nom->setObjectName(QString::fromUtf8("nom"));
        nom->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(nom);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Sitka\";"));

        horizontalLayout_2->addWidget(label_2);

        mdp = new QLineEdit(groupBox);
        mdp->setObjectName(QString::fromUtf8("mdp"));
        mdp->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(mdp);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        connexion = new QPushButton(groupBox);
        connexion->setObjectName(QString::fromUtf8("connexion"));
        connexion->setMinimumSize(QSize(0, 0));
        connexion->setStyleSheet(QString::fromUtf8("\n"
"font: 9pt \"Sitka\";\n"
"\n"
""));

        horizontalLayout_3->addWidget(connexion);

        quitter = new QPushButton(groupBox);
        quitter->setObjectName(QString::fromUtf8("quitter"));
        quitter->setStyleSheet(QString::fromUtf8("font: 9pt \"Sitka\";"));

        horizontalLayout_3->addWidget(quitter);


        verticalLayout->addLayout(horizontalLayout_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1131, 771));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/img/img/back.png);"));
        MainWindow->setCentralWidget(centralwidget);
        widget->raise();
        groupBox->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1125, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(quitter, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "S'identifier", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">nom &amp; pr\303\251nom</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">mot de passe</span></p></body></html>", nullptr));
        connexion->setText(QCoreApplication::translate("MainWindow", "connexion", nullptr));
        quitter->setText(QCoreApplication::translate("MainWindow", "quitter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
