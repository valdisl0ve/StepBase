#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_main->hide();

    ui->btnOk->hide();
    ui->btnOkEport->hide();
    ui->btnOkFind->hide();


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    model->insertRow(model->rowCount());
    ui->listWidget->addItem("INSERT ROW");
}

void MainWindow::on_btndelete_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0 ) {
    model->removeRow(selectedRow);
 model->select();
  ui->listWidget->addItem("DELETING ROW");
    } else {
        ui->listWidget->addItem("NO ROW SELECTED");
    }
}



void MainWindow::on_btnOk_clicked()
{
    data_path = ui->input_main->text();


    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(data_path);

    if (db.open() == false) {
    ui->listWidget->addItem("DATABASE ERROR");
    return;
    }
    else {
          qDebug() << "ALL RIGHT!";
          ui->listWidget->addItem("DATABASE IMPORTED FROM SQLITE " + data_path);

    }

    model = new QSqlTableModel(this, db);
    model -> setTable("table_person");
    model->select();
    ui->tableView->setModel(model);

   



    ui->input_main->hide();
    ui->btnOk->hide();
}

void MainWindow::on_btnData_clicked()
{
    ui->input_main->clear();
    ui->input_main->show();
    ui->btnOk->show();
}

void MainWindow::on_btnExport_clicked()
{
    ui->input_main->show();
    ui->btnOkEport->show();
    ui->input_main->clear();
}

void MainWindow::on_btnOkEport_clicked()
{
    ui->input_main->hide();
    ui->btnOkEport->hide();
    export_path = ui->input_main->text();
    ui->listWidget->addItem("DATABASE WAS EXPORTED TO " + export_path);
     QSqlQuery query = QSqlQuery(db);
                if(!query.exec("select* from table_person")){
                         return;
    }
                while(query.next()) {
                export_all = export_all + query.value(0).toString()
                        + ";" + query.value(1).toString() + ";"
                        + query.value(2).toString() + "; " + query.value(3).toString() + "\n";
                }


               // write to file

               QFile file(export_path);

               if (file.open(QIODevice::WriteOnly))
               {
                   file.write(export_all.toLocal8Bit());

                   file.close();
               }


               file.close();
                export_all = "";
    
    
}

void MainWindow::on_btn_find_clicked()
{
    ui->btnOkFind->show();
    ui->input_main->show();
    ui->input_main->clear();
}

void MainWindow::on_btnOkFind_clicked()
{
    QString find =  ui->input_main->text();
QSqlQuery query = QSqlQuery(db);
          if(!query.exec("select* from table_person")){
                   return;
}
          while(query.next()) {
             if (find == query.value(0) || find == query.value(1) || find == query.value(2) || find == query.value(3) ){
                 QString row_find = query.value(0).toString()
                         + "; " + query.value(1).toString() + "; "
                         + query.value(2).toString() + "; " + query.value(3).toString();

                 ui->input_main->clear();
                 ui->listWidget->addItem("FOUND " + row_find);
             }
          }
         ui->btnOkFind->hide();
         ui->input_main->hide();
}
