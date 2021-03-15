#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>



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
    

    void on_btnAdd_clicked();

    void on_btndelete_clicked();

    void on_btnOk_clicked();

    void on_btnData_clicked();

    void on_btnExport_clicked();

    void on_btnOkEport_clicked();

    void on_btn_find_clicked();

    void on_btnOkFind_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    QString data_path;
    QString export_path;

    QString export_all;
    int countRow();


//public slots:
 //   void exportCSV();
};
#endif // MAINWINDOW_H
