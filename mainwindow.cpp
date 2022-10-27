#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), labels(new std::vector<Label>), toppings(new std::vector<Topping>), pizzas(new std::vector<Pizza>)
{
    ui->setupUi(this);
    QObject::connect(ui->label_listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(setLabel(QListWidgetItem*)));
    QObject::connect(ui->topping_listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(setTopping(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    //
}


void MainWindow::on_addButton_clicked()
{
    std::string name = ui->nameLineEdit->text().toStdString();
    int mode = ui->modeWidget->currentIndex();
    labels->push_back({name, mode});

    ui->existinglabel_listWidget->addItem(QString::fromStdString(name + " [" + std::to_string(mode) + "]"));

    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(name));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    ui->label_listWidget->addItem(item);
}

void MainWindow::setLabel(QListWidgetItem* item)
{
    for (Label &l: *labels)
    {
        if (item->text().toStdString() == l.name) { l.selected = !l.selected; }
    }
}

void MainWindow::on_addButton_2_clicked()
{
    std::string name = ui->nameLineEdit_2->text().toStdString();
    int price = ui->priceLineEdit->value();
    std::vector<Label> selected_labels = {};

    std::string all_labels = "";
    for (Label l: *labels)
    {
        if (l.selected) { selected_labels.push_back(l); all_labels += l.name + " "; }
    }

    toppings->push_back({name, price, selected_labels});

    ui->existingtopping_listWidget->addItem(QString::fromStdString(name + " [" + std::to_string(price) + " " + all_labels + "]"));

    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(name));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    ui->topping_listWidget->addItem(item);
}

void MainWindow::setTopping(QListWidgetItem* item)
{
    for (Topping &t: *toppings)
    {
        if (item->text().toStdString() == t.name) { t.selected = !t.selected; }
    }
}


void MainWindow::on_addButton_3_clicked()
{
    std::string name = ui->nameLineEdit_3->text().toStdString();
    int base_price = ui->basepriceSpinBox->value();
    std::vector<Topping> selected_toppings = {};

    std::string all_toppings = "";
    for (Topping t: *toppings)
    {
        if (t.selected) { selected_toppings.push_back(t); all_toppings += t.name + " "; }
    }

    Pizza pizza(name, base_price, selected_toppings);
    pizzas->push_back(pizza);

    std::string all_labels = "";
    for (Label l: pizzas->back().labels)
    {
        all_labels += l.name + " ";
    }

    ui->existingpizza_listWidget->addItem(QString::fromStdString(name + " [" + std::to_string(base_price) + " " + all_toppings + all_labels + std::to_string(pizzas->back().full_price) + " " + "]"));
}

