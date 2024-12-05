#ifndef NOTIF_H
#define NOTIF_H
#include <QSystemTrayIcon>
#include<QString>

class notif
{
public:
    notif();
    void notif_ajoutboutique();

    void notif_supprimerboutique();

    void notif_modifierboutique();

    void notif_failed();


};

#endif // NOTIF_H
