#include "mainwindow.h"
#include <QApplication>
#include<QMessageBox>
#include"connection.h"
#include "acceuil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test= c.createconnection();
    MainWindow w;
    acceuil acc;
    if(test)
    {
    w.show();
        QMessageBox::information(nullptr,QObject::tr("datbase is open"),QObject::tr("connection successful.\n""click cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("datbase is not open"),QObject::tr("connection failed.\n""click cancel to exit"),QMessageBox::Cancel);

    return a.exec();
}
