/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
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
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1125, 708);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(590, 150, 361, 381));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font.setPointSize(10);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 21, 155);"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font1.setPointSize(8);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        nom = new QLineEdit(groupBox);
        nom->setObjectName("nom");
        nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));

        horizontalLayout->addWidget(nom);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font2.setPointSize(8);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_2);

        mdp = new QLineEdit(groupBox);
        mdp->setObjectName("mdp");
        mdp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        mdp->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(mdp);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        connexion = new QPushButton(groupBox);
        connexion->setObjectName("connexion");
        connexion->setMinimumSize(QSize(0, 0));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font3.setPointSize(9);
        font3.setBold(false);
        font3.setItalic(false);
        connexion->setFont(font3);
        connexion->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 21, 155);\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_3->addWidget(connexion);

        quitter = new QPushButton(groupBox);
        quitter->setObjectName("quitter");
        quitter->setFont(font3);
        quitter->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 21, 155);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(quitter);


        verticalLayout->addLayout(horizontalLayout_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 1131, 771));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/img/img/back.png);"));
        MainWindow->setCentralWidget(centralwidget);
        widget->raise();
        groupBox->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1125, 17));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(quitter, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "S'identifier", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:400; color:#00159b;\">nom &amp; pr\303\251nom</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00159b;\">mot de passe </span></p></body></html>", nullptr));
        connexion->setText(QCoreApplication::translate("MainWindow", "connexion", nullptr));
        quitter->setText(QCoreApplication::translate("MainWindow", "quitter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
