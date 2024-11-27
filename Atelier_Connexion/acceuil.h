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

    void on_pushButton_16_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_pushButton_14_clicked();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_pushButton_15_clicked();

    void createPieChart();

    void on_pushButton_21_clicked();

private:
    Ui::acceuil *ui;
};

#endif // ACCEUIL_H
