#include "mainwindow.h"
#include "connection.h"
#include"acceuil.h"
//#include"ArduinoDatabaseLink.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection c;
    bool testc = c.createConnection();



    MainWindow w;
    acceuil acc;

    ArduinoDatabaseLink arduinoLink(&acc);

    if (testc)
    {
        w.show();
        QMessageBox::information(nullptr,"DATABASE","succès de connexion !");
    }
    else
    {
        QMessageBox::warning(nullptr,"DATABASE","ERREUR DE CONNEXION");
    }
    return a.exec();
}
