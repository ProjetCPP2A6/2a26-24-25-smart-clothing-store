#ifndef ARDUINODATABASELINK_H
#define ARDUINODATABASELINK_H

#include <QObject>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class ArduinoDatabaseLink : public QObject {
    Q_OBJECT

public:
    explicit ArduinoDatabaseLink(QObject *parent = nullptr);
    ~ArduinoDatabaseLink();

private slots:
    void readFromArduino();

private:
    QSerialPort* serial;
    QSqlDatabase db;
};

#endif // ARDUINODATABASELINK_H
