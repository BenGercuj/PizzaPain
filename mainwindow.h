#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QFileDialog>
#include "structs.hpp"

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
    void on_tabWidget_currentChanged(int index);

    void on_addButton_clicked();

    void setLabel(QListWidgetItem* item);

    void on_addButton_2_clicked();

    void setTopping(QListWidgetItem* item);

    void on_addButton_3_clicked();

    void on_save_pushButton_clicked();

    void on_actionKil_p_s_triggered();

    void on_actionKiment_s_triggered();

    void on_actionBet_lt_s_triggered();

    void on_actionGener_l_s_triggered();

private:
    Ui::MainWindow *ui;

    std::vector<Label> *labels;
    std::vector<Topping> *toppings;
    std::vector<Pizza> *pizzas;
    Basics *basics;

};
#endif // MAINWINDOW_H
