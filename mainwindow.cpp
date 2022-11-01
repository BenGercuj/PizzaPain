#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), labels(new std::vector<Label>), toppings(new std::vector<Topping>), pizzas(new std::vector<Pizza>), basics(new Basics)
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


void MainWindow::on_save_pushButton_clicked()
{
    basics->name = ui->shopnameLineEdit->text();
    basics->transport_cost = ui->transportcostspinBox->value();
    basics->open_hours[0].first = ui->mStart->time().toString(); basics->open_hours[0].second = ui->mEnd->time().toString();
    basics->open_hours[1].first = ui->tStart->time().toString(); basics->open_hours[1].second = ui->tEnd->time().toString();
    basics->open_hours[2].first = ui->wStart->time().toString(); basics->open_hours[2].second = ui->wEnd->time().toString();
    basics->open_hours[3].first = ui->thStart->time().toString(); basics->open_hours[3].second = ui->thEnd->time().toString();
    basics->open_hours[4].first = ui->fStart->time().toString(); basics->open_hours[4].second = ui->fEnd->time().toString();
    basics->open_hours[5].first = ui->satStart->time().toString(); basics->open_hours[5].second = ui->satEnd->time().toString();
    basics->open_hours[6].first = ui->sunStart->time().toString(); basics->open_hours[6].second = ui->sunEnd->time().toString();
}


void MainWindow::on_actionKil_p_s_triggered()
{
    QCoreApplication::quit();
}


void MainWindow::on_actionKiment_s_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Mentés"), "/home/state.pizzapain", tr("Very Special Totally Not Text Files (*.pizzapain)"));

    if (!filename.isNull())
    {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(&file);

            ts << basics->name << ';' << basics->transport_cost << "\n";
            for (size_t i = 0; i < 7; i++)
            {
                ts << basics->open_hours->first << '-' << basics->open_hours->second;
                if (i != 6) { ts << ';'; } else { ts << "\n"; }
            }

            for (size_t i = 0; i < labels->size(); i++)
            {
                ts << QString::fromStdString((*labels)[i].name) << ';' << (*labels)[i].mode << "\n";
            }
            ts << "#\n";

            for (size_t i = 0; i < toppings->size(); i++)
            {
                ts << QString::fromStdString((*toppings)[i].name) << ';' << (*toppings)[i].price;
                for (size_t j = 0; j < (*toppings)[i].labels.size(); j++)
                {
                    ts << ';' << QString::fromStdString((*toppings)[i].labels[j].name);
                }
                ts << "\n";
            }
            ts << "##\n";

            for (size_t i = 0; i < pizzas->size(); i++)
            {
                ts << QString::fromStdString((*pizzas)[i].name) << ';' << (*pizzas)[i].base_price << "\n";
                for (size_t j = 0; j < (*pizzas)[i].toppings.size(); j++)
                {
                    ts << QString::fromStdString((*pizzas)[i].toppings[j].name);
                    if (j != (*pizzas)[i].toppings.size()-1) { ts << ';'; } else { ts << "\n"; }
                }
            }
        }

        file.close();
    }
}


void MainWindow::on_actionBet_lt_s_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Megnyitás"), "/home/state.pizzapain", tr("Very Special Totally Not Text Files (*.pizzapain)"));

    if (!filename.isNull())
    {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //
        }
    }
}

