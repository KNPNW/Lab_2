#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <string>
#include <vector>
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    string value, date;
    value = ui->valueEdit->text().toStdString();
    if(value != ""){
        date = ui->dateEdit->text().toStdString();
        Data dFPush(stoi(date.substr(0,2)), stoi(date.substr(3,5)), stoi(date.substr(7,9)));
        mainTree.push(dFPush, value);
        treatment();
    }else
        QMessageBox::critical(0, "Внимание","Не введено явление!");
}

void MainWindow::treatment(){
    ui->textBrowser->clear();
    vector<Data> dates = mainTree.getKeys();
    vector<string> values = mainTree.getValues();
    for (int i = 0; i < int(dates.size()); i++) {
        string day, month, year;
        int dayI, monthI, yearI;
        dayI = dates[i].getDay();
        monthI = dates[i].getMonth();
        yearI = dates[i].getYear();

        stringstream s1, s2, s3;
        s1 << dayI;
        s2 << monthI;
        s3 << yearI;
        day = s1.str();
        month = s2.str();
        year = s3.str();
        if(dayI < 10)
            day.insert(0, "0");
        if(monthI < 10)
            month.insert(0, "0");
        if(yearI >= 100){
            year.insert(0, "2");
        }else if (yearI > 10){
            year.insert(0, "20");
        }else{
            year.insert(0, "200");
        }

        QString item = (QString("Дата - ")
                        +QString(day.c_str())
                        +QString(".")
                        +QString(month.c_str())
                        +QString(".")
                        +QString(year.c_str())
                        +QString("\n")
                        +QString(values[i].c_str())
                        +QString("\n"));
        ui->textBrowser->append(item);
    }
}

void MainWindow::on_action_4_triggered()
{
    mainTree.delAll();
    ui->textBrowser->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    string date = ui->dateEdit_2->text().toStdString();
    Data dFDel(stoi(date.substr(0,2)), stoi(date.substr(3,5)), stoi(date.substr(7,9)));
    if(mainTree.isKey(dFDel)){
        mainTree.del(dFDel);
        treatment();
    }else
        QMessageBox::critical(0, "Внимание","Запись с указанной датой не найдена!");
}

void MainWindow::on_action_triggered()
{
    QString qs = QFileDialog::getOpenFileName(this, "Open MusComopirions", ".", "TEXT files (*.txt)");
    std::string filename = qs.toUtf8().constData();
    try {
        if (mainTree.getSize() > 0)
            mainTree.delAll();
        mainTree.fromFile(filename);
        treatment();
    } catch (exception) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при чтении данных");
    }
}



void MainWindow::on_action_3_triggered()
{
    QString qs = QFileDialog::getSaveFileName(this, "Save the file");
    std::string filename = qs.toUtf8().constData();
    mainTree.toFile(filename);
}
