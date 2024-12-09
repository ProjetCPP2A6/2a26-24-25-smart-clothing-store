#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"acceuil.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connexion_clicked();

    void on_mdp_returnPressed();

    void on_nom_returnPressed();

private:
    Ui::MainWindow *ui;
    acceuil *acc;
};
#endif // MAINWINDOW_H
