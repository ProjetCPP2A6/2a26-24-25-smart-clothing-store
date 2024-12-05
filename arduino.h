#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();
    int connect_arduino(); // Connecter Arduino
    int close_arduino(); // Fermer la connexion
    int write_to_arduino(QByteArray); // Envoyer des données à Arduino
    QByteArray read_from_arduino();  // Lire des données depuis Arduino
    QSerialPort* getserial(); // Retourner l'objet QSerialPort
    QString getarduino_port_name(); // Retourner le nom du port
private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_producy_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
