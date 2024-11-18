#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QMainWindow>

namespace Ui {
class acceuil;
}

class acceuil : public QMainWindow
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::acceuil *ui;
};

#endif // ACCEUIL_H
