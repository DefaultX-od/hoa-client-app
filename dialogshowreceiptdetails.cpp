#include "dialogshowreceiptdetails.h"
#include "ui_dialogshowreceiptdetails.h"

#include "dbconnector.h"
#include "dialogaddrow.h"
#include "library.h"
#include "dialogconfirmation.h"

DialogShowReceiptDetails::DialogShowReceiptDetails(int idReceipt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowReceiptDetails)
{
    ui->setupUi(this);

    id=idReceipt;

    tableViewUpdate();
}

DialogShowReceiptDetails::~DialogShowReceiptDetails()
{
    delete ui;
}

void DialogShowReceiptDetails::tableViewUpdate(){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from receipt_decomposition("+QString::number(id)+")");

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
}

void DialogShowReceiptDetails::on_pushButtonAddRow_clicked()
{
    DialogAddRow *dialogAddrow=new DialogAddRow(4, QString::number(id), this);
    qDebug()<<QString::number(id)<<"это id квитанции";
    dialogAddrow->exec();
    tableViewUpdate();
}


void DialogShowReceiptDetails::on_pushButtonEditRow_clicked()
{
    QString idStr=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QVector <QString> data;
    QSqlQueryModel *dataModel =new QSqlQueryModel();

    QSqlQuery query;
    query.prepare(library::getItemQuery(4));

    query.addBindValue(idStr);
    query.exec();
    dataModel->setQuery(query);

    qDebug()<<"Изменяем детали "<<idStr;



    for(auto j=0; j<dataModel->columnCount(); j++){
        data.push_back(dataModel->record(0).field(j).value().toString());
        qDebug()<<"Данные для внесения "<<data[j];
    }

    data.push_front(idStr);

    DialogAddRow dialogAddrow(4, data, this);
    dialogAddrow.exec();
    tableViewUpdate();
}


void DialogShowReceiptDetails::on_pushButtonRemoveRow_clicked()
{
    DialogConfirmation confirm;
    if(confirm.exec()==QDialog::Accepted){
    int queryNum = 4;
    int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    QSqlQuery query;
    query.prepare(library::getDeleteItemQuery(queryNum));
    query.addBindValue(id);
    query.exec();
    tableViewUpdate();
    qDebug()<<QString::number(id);
    }
}

