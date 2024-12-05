#include "notif.h"
#include <QSystemTrayIcon>
#include<QString>

notif::notif()
{

}

void notif::notif_ajoutboutique()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/logo bleu.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des boutiques ","nouveau boutique est ajouté ",QSystemTrayIcon::Information,15000);
    srand (time(NULL));
}

void notif::notif_supprimerboutique(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/logo bleu.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des boutiques","un boutique est supprimé",QSystemTrayIcon::Information,15000);
    srand (time(NULL));
}


void notif::notif_modifierboutique(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/logo bleu.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des boutiques ","boutique modifié",QSystemTrayIcon::Information,15000);
    srand (time(NULL));
}


void notif::notif_failed(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/logo bleu.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des boutiques ","action failed",QSystemTrayIcon::Critical,15000);
    srand (time(NULL));
}








