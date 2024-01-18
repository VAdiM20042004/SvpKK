#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./MedLabaDB2.db");
    if(db.open())
    {
        qDebug("OPEN");
    }
    else
    {
        qDebug("NO OPEN");
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE MedLaba(Name TEXT, Specialist TEXT, Time TEXT, Cost INT);");

    model = new QSqlTableModel(this, db);
    model->setTable("MedLaba");
    model->select();

    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addRow_clicked()
{
    model->insertRow(model->rowCount(QModelIndex()));
}
void MainWindow::on_deleteRow_clicked()
{
    model->removeRow(row);
}
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
