/********************************************************************************
** Form generated from reading UI file 'acceuil.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCEUIL_H
#define UI_ACCEUIL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_acceuil
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_7;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_10;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *yassine;
    QWidget *yassine_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget_3;
    QWidget *tab_9;
    QWidget *tab_10;
    QWidget *page_2;
    QLabel *label_3;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget_4;
    QWidget *tab_11;
    QWidget *tab_12;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget_5;
    QWidget *tab_13;
    QWidget *tab_14;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_6;
    QWidget *tab_7;
    QWidget *tab_8;
    QMenuBar *menubar;

    void setupUi(QMainWindow *acceuil)
    {
        if (acceuil->objectName().isEmpty())
            acceuil->setObjectName("acceuil");
        acceuil->resize(1107, 678);
        acceuil->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);"));
        acceuil->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        acceuil->setTabShape(QTabWidget::TabShape::Rounded);
        centralwidget = new QWidget(acceuil);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(100, 100));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/2.png);"));
        label->setScaledContents(true);

        verticalLayout_2->addWidget(label);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");

        verticalLayout_2->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icones/icone/stock.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/icones/icone/stock.png"), QSize(), QIcon::Mode::Disabled, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(30, 30));
        pushButton->setCheckable(true);
        pushButton->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(50, 50));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icone/achat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/icone/achat.png"), QSize(), QIcon::Mode::Disabled, QIcon::State::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(30, 30));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(50, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icones/icone/cients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(30, 30));
        pushButton_3->setCheckable(true);
        pushButton_3->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(50, 50));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icones/icone/personnel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(30, 30));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(50, 50));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icones/icone/boutique.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(30, 30));
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(50, 50));
        pushButton_6->setMouseTracking(true);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);\n"
"color: rgb(0, 0, 0);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icones/icone/livrasion.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_6->setIcon(icon5);
        pushButton_6->setIconSize(QSize(30, 30));
        pushButton_6->setCheckable(true);
        pushButton_6->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(50, 50));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icones/icone/quitter.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_7->setIcon(icon6);
        pushButton_7->setIconSize(QSize(30, 30));
        pushButton_7->setCheckable(true);
        pushButton_7->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_7);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName("gridLayout_3");
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_8 = new QPushButton(widget_3);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMinimumSize(QSize(50, 50));
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icones/icone/menu.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_8->setIcon(icon7);
        pushButton_8->setIconSize(QSize(30, 30));
        pushButton_8->setCheckable(true);
        pushButton_8->setChecked(false);
        pushButton_8->setAutoRepeat(false);
        pushButton_8->setAutoExclusive(false);
        pushButton_8->setAutoRepeatDelay(0);
        pushButton_8->setAutoRepeatInterval(0);

        horizontalLayout_2->addWidget(pushButton_8);

        horizontalSpacer = new QSpacerItem(296, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        lineEdit = new QLineEdit(widget_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(100, 0));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(lineEdit);

        pushButton_9 = new QPushButton(widget_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setMinimumSize(QSize(50, 50));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icones/icone/serach.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_9->setIcon(icon8);
        pushButton_9->setIconSize(QSize(30, 30));
        pushButton_9->setCheckable(true);
        pushButton_9->setAutoExclusive(true);

        horizontalLayout->addWidget(pushButton_9);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(300, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_10 = new QPushButton(widget_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setMinimumSize(QSize(50, 50));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 241, 229);"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icones/icone/reglage.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_10->setIcon(icon9);
        pushButton_10->setIconSize(QSize(30, 30));
        pushButton_10->setCheckable(true);
        pushButton_10->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pushButton_10);


        gridLayout_3->addWidget(widget_3, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(false);
        tabWidget->setStyleSheet(QString::fromUtf8("\n"
"QTabBar::tab:selected {\n"
"    background:#004aad;\n"
"    border-color: black;\n"
"    border-bottom-color: black; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: rgb(0, 0, 0);\n"
"    margin-top:10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f5f1e5;\n"
"    border: 2px;\n"
"    border-bottom-color: black; \n"
"    min-width: 25ex;\n"
"    padding:1px;\n"
"}\n"
"\n"
""));
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setElideMode(Qt::TextElideMode::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        yassine = new QWidget();
        yassine->setObjectName("yassine");
        tabWidget->addTab(yassine, QString());
        yassine_2 = new QWidget();
        yassine_2->setObjectName("yassine_2");
        tabWidget->addTab(yassine_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget->addTab(tab_5, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        verticalLayout_5 = new QVBoxLayout(page_6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        tabWidget_3 = new QTabWidget(page_6);
        tabWidget_3->setObjectName("tabWidget_3");
        tabWidget_3->setStyleSheet(QString::fromUtf8("\n"
"QTabBar::tab:selected {\n"
"    background:#004aad;\n"
"    border-color: black;\n"
"    border-bottom-color: black; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: rgb(0, 0, 0);\n"
"    margin-top:10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f5f1e5;\n"
"    border: 2px;\n"
"    border-bottom-color: black; \n"
"    min-width: 25ex;\n"
"    padding:1px;\n"
"}\n"
"\n"
""));
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        tabWidget_3->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        tabWidget_3->addTab(tab_10, QString());

        verticalLayout_5->addWidget(tabWidget_3);

        stackedWidget->addWidget(page_6);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(330, 190, 241, 91));
        label_3->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(0, 0, 0);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        verticalLayout_6 = new QVBoxLayout(page_3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        tabWidget_4 = new QTabWidget(page_3);
        tabWidget_4->setObjectName("tabWidget_4");
        tabWidget_4->setStyleSheet(QString::fromUtf8("\n"
"QTabBar::tab:selected {\n"
"    background:#004aad;\n"
"    border-color: black;\n"
"    border-bottom-color: black; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: rgb(0, 0, 0);\n"
"    margin-top:10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f5f1e5;\n"
"    border: 2px;\n"
"    border-bottom-color: black; \n"
"    min-width: 25ex;\n"
"    padding:1px;\n"
"}\n"
"\n"
""));
        tab_11 = new QWidget();
        tab_11->setObjectName("tab_11");
        tabWidget_4->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName("tab_12");
        tabWidget_4->addTab(tab_12, QString());

        verticalLayout_6->addWidget(tabWidget_4);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        verticalLayout_7 = new QVBoxLayout(page_4);
        verticalLayout_7->setObjectName("verticalLayout_7");
        tabWidget_5 = new QTabWidget(page_4);
        tabWidget_5->setObjectName("tabWidget_5");
        tabWidget_5->setStyleSheet(QString::fromUtf8("\n"
"QTabBar::tab:selected {\n"
"    background:#004aad;\n"
"    border-color: black;\n"
"    border-bottom-color: black; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: rgb(0, 0, 0);\n"
"    margin-top:10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f5f1e5;\n"
"    border: 2px;\n"
"    border-bottom-color: black; \n"
"    min-width: 25ex;\n"
"    padding:1px;\n"
"}\n"
"\n"
""));
        tab_13 = new QWidget();
        tab_13->setObjectName("tab_13");
        tabWidget_5->addTab(tab_13, QString());
        tab_14 = new QWidget();
        tab_14->setObjectName("tab_14");
        tabWidget_5->addTab(tab_14, QString());

        verticalLayout_7->addWidget(tabWidget_5);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        verticalLayout_3 = new QVBoxLayout(page_5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tabWidget_2 = new QTabWidget(page_5);
        tabWidget_2->setObjectName("tabWidget_2");
        QFont font;
        font.setBold(true);
        tabWidget_2->setFont(font);
        tabWidget_2->setMouseTracking(true);
        tabWidget_2->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        tabWidget_2->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
        tabWidget_2->setAcceptDrops(true);
        tabWidget_2->setStyleSheet(QString::fromUtf8("\n"
"QTabBar::tab:selected {\n"
"    background:#004aad;\n"
"    border-color: black;\n"
"    border-bottom-color: black; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	color: rgb(0, 0, 0);\n"
"    margin-top:10px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f5f1e5;\n"
"    border: 2px;\n"
"    border-bottom-color: black; \n"
"    min-width: 25ex;\n"
"    padding:1px;\n"
"}\n"
"\n"
""));
        tabWidget_2->setTabShape(QTabWidget::TabShape::Rounded);
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget_2->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        tabWidget_2->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        tabWidget_2->addTab(tab_8, QString());

        verticalLayout_3->addWidget(tabWidget_2);

        stackedWidget->addWidget(page_5);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);


        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        acceuil->setCentralWidget(centralwidget);
        widget_2->raise();
        widget->raise();
        menubar = new QMenuBar(acceuil);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1107, 25));
        acceuil->setMenuBar(menubar);

        retranslateUi(acceuil);
        QObject::connect(pushButton_7, &QPushButton::clicked, acceuil, qOverload<>(&QMainWindow::close));
        QObject::connect(pushButton_8, &QPushButton::toggled, widget, &QWidget::setVisible);

        stackedWidget->setCurrentIndex(4);
        tabWidget->setCurrentIndex(0);
        tabWidget_4->setCurrentIndex(1);
        tabWidget_5->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(acceuil);
    } // setupUi

    void retranslateUi(QMainWindow *acceuil)
    {
        acceuil->setWindowTitle(QCoreApplication::translate("acceuil", "MainWindow", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("acceuil", "     Produits", nullptr));
        pushButton_2->setText(QCoreApplication::translate("acceuil", "       Achats", nullptr));
        pushButton_3->setText(QCoreApplication::translate("acceuil", "     Clients", nullptr));
        pushButton_4->setText(QCoreApplication::translate("acceuil", "  Personnel", nullptr));
        pushButton_5->setText(QCoreApplication::translate("acceuil", " Boutiques", nullptr));
        pushButton_6->setText(QCoreApplication::translate("acceuil", " Livraisons", nullptr));
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(yassine), QCoreApplication::translate("acceuil", "yassine", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(yassine_2), QCoreApplication::translate("acceuil", "Tab 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("acceuil", "Page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("acceuil", "Page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("acceuil", "Page", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_9), QCoreApplication::translate("acceuil", "Tab 1", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_10), QCoreApplication::translate("acceuil", "Tab 2", nullptr));
        label_3->setText(QCoreApplication::translate("acceuil", "<html><head/><body><p align=\"center\">personne</p></body></html>", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_11), QCoreApplication::translate("acceuil", "Tab 1", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_12), QCoreApplication::translate("acceuil", "Tab 2", nullptr));
        tabWidget_5->setTabText(tabWidget_5->indexOf(tab_13), QCoreApplication::translate("acceuil", "Tab 1", nullptr));
        tabWidget_5->setTabText(tabWidget_5->indexOf(tab_14), QCoreApplication::translate("acceuil", "Tab 2", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("acceuil", "m\303\251tier 1", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("acceuil", "m\303\251tier 2 ", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("acceuil", "m\303\251tier 3", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QCoreApplication::translate("acceuil", "m\303\251tier 4", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QCoreApplication::translate("acceuil", "m\303\251tier 5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class acceuil: public Ui_acceuil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCEUIL_H
