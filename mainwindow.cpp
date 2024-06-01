#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbconnector.h"
#include "dialogshowreceiptdetails.h"
#include "dialogaddrow.h"
#include "dialogconfirmation.h"

#include "library.h"

void MainWindow::tableViewUpdate(){
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel;
    if(!filterQuery.isEmpty()){
        query.prepare(filterQuery);
        for(auto valuesToBind : valuesToBind)
            query.addBindValue(valuesToBind);
    }
    else{
        query.prepare(tableQuery);
    }
    query.exec();
    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::setFiltersDataConstraints(){
    QSqlQueryModel *modelStates = new QSqlQueryModel;
    modelStates->setQuery("SELECT get_states()");

    QSqlQueryModel *modelAddress = new QSqlQueryModel;
    modelAddress->setQuery("SELECT * from get_addresses()");

    QSqlQueryModel *modelPeriod = new QSqlQueryModel;
    modelPeriod->setQuery("SELECT * from get_periods()");

    QList<QComboBox*> comboBoxes=ui->stackedWidgetFilters->findChildren<QComboBox*>();

    for(auto comboBox : comboBoxes){
        if(comboBox->objectName().contains("comboBoxAddress")){
            comboBox->setModel(modelAddress);
            comboBox->setModelColumn(1);
        }
        else if(comboBox->objectName().contains("comboBoxPeriod")){
            comboBox->setModel(modelPeriod);
        }
        else if(comboBox->objectName().contains("comboBoxState")){
            comboBox->setModel(modelStates);
        }
        comboBox->setCurrentIndex(-1);
    }
}

void MainWindow::setDataEditState(bool state){
    const QList<QPushButton*> editButtons = ui->widgetEditSection->findChildren<QPushButton*>();
    for (QPushButton *editButton : editButtons) {
        editButton->setEnabled(state);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidgetFilters->setEnabled(ui->checkBox->isChecked());

    DBConnector *dbConnector= new DBConnector();
    dbConnector->db.open();

    if(dbConnector->db.isOpen()){
        qDebug()<<"База открыта!";
    }
    else{
        qDebug()<<"База не открыта!";
    }
    ui->comboBoxTableSelect->setCurrentIndex(0);
    setFiltersDataConstraints();

    tableQuery=library::getMainQuery(0);
    tableViewUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBoxTableSelect_currentIndexChanged(int index)
{
    setDataEditState(true);
    ui->stackedWidgetFilters->setCurrentIndex(index);

    ui->comboBoxStateSelect->setCurrentIndex(-1);

    for (int i = 0; i < ui->stackedWidgetFilters->count (); ++i)
    {
        QSizePolicy::Policy policy = QSizePolicy::Ignored;
        if (i == ui->stackedWidgetFilters->currentIndex ())
            policy = QSizePolicy::Maximum;

        QWidget* pPage = ui->stackedWidgetFilters->widget(i);
        pPage->setSizePolicy (policy, policy);
    }

    if(index==4){
        setDataEditState(false);
    }

    filterQuery.clear();
    valuesToBind.clear();
    tableQuery=library::getMainQuery(index);
    tableViewUpdate();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    switch (ui->comboBoxTableSelect->currentIndex()){
    case 3:{
        idReceipt=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

        DialogShowReceiptDetails dialog(idReceipt, this);
        dialog.exec();
        break;
    }
    }
}

void MainWindow::on_pushButtonAddRow_clicked()
{
    DialogAddRow dialogAddrow(ui->comboBoxTableSelect->currentIndex(),this);
    dialogAddrow.exec();
    QList<QComboBox*> comboBoxes=ui->stackedWidgetFilters->findChildren<QComboBox*>();
    for(auto comboBox : comboBoxes){
        comboBox->setCurrentIndex(-1);
    }
    filterQuery.clear();
    tableViewUpdate();
    setFiltersDataConstraints();
}

void MainWindow::on_pushButtonEditRow_clicked()
{
    QVector <QString> data;
    QSqlQueryModel *dataModel =new QSqlQueryModel();
    int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();

    QSqlQuery query;
    query.prepare(library::getItemQuery(ui->comboBoxTableSelect->currentIndex()));

    query.addBindValue(id);
    query.exec();
    dataModel->setQuery(query);

    for(auto j=0; j<dataModel->columnCount(); j++){
        data.push_back(dataModel->record(0).field(j).value().toString());
    }

    DialogAddRow dialogAddrow(ui->comboBoxTableSelect->currentIndex(), data, this);
    dialogAddrow.exec();
    filterQuery.clear();
    tableViewUpdate();
    setFiltersDataConstraints();
}

void MainWindow::on_comboBoxStateSelect_currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        QSqlQuery query;
        QSqlQueryModel *model = new QSqlQueryModel;
        query.prepare("select distinct b.city from buildings b where b.state=?");
        query.addBindValue(arg1);
        query.exec();
        model->setQuery(query);

        ui->comboBoxCitySelect->setModel(model);
        ui->comboBoxCitySelect->setCurrentIndex(-1);

        filterQuery=library::getFilterState();
        qDebug()<<filterQuery;
        valuesToBind.clear();
        valuesToBind.push_back(arg1);

        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->stackedWidgetFilters->setEnabled(ui->checkBox->isChecked());
    if(!ui->stackedWidgetFilters->isEnabled()){
        QList<QComboBox*> comboBoxes=ui->stackedWidgetFilters->findChildren<QComboBox*>();
        for(auto comboBox : comboBoxes){
            comboBox->setCurrentIndex(-1);
        }
        filterQuery.clear();
        tableViewUpdate();
    }
}

void MainWindow::on_comboBoxAddressSelect_A_currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        valuesToBind.clear();
        valuesToBind.push_back(arg1);
        filterQuery=library::getFilterAddressApartments();
        qDebug()<<filterQuery;
        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

void MainWindow::on_pushButtonRemoveRow_clicked()
{
    DialogConfirmation confirm;
    if(confirm.exec()==QDialog::Accepted){
    int queryNum = ui->comboBoxTableSelect->currentIndex();
    int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    QSqlQuery query;
    query.prepare(library::getDeleteItemQuery(queryNum));
    query.addBindValue(id);
    query.exec();
    filterQuery.clear();
    tableViewUpdate();
    setFiltersDataConstraints();
}
}

void MainWindow::on_comboBoxCitySelect_currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        valuesToBind.clear();
        valuesToBind.push_back(ui->comboBoxStateSelect->currentText());
        valuesToBind.push_back(arg1);
        filterQuery=library::getFilterCity();
        qDebug()<<filterQuery;
        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

void MainWindow::on_comboBoxPeriodSelect__currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        valuesToBind.clear();
        valuesToBind.push_back(arg1);
        filterQuery=library::getFilterPeriodReceipts();
        qDebug()<<filterQuery;
        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

void MainWindow::on_comboBoxPeriodSelect_1_currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        valuesToBind.clear();
        valuesToBind.push_back(arg1);
        filterQuery=library::getFilterPeriodMeterData();
        qDebug()<<filterQuery;
        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

void MainWindow::on_comboBoxAddressSelect_O_currentTextChanged(const QString &arg1)
{
    if(ui->stackedWidgetFilters->isEnabled()){
        valuesToBind.clear();
        valuesToBind.push_back(arg1);
        filterQuery=library::getFilterAddressOwners();
        qDebug()<<filterQuery;
        tableViewUpdate();
    }
    else{
        tableViewUpdate();
    }
}

