#include "dialogaddrow.h"
#include "ui_dialogaddrow.h"
#include <typeinfo>
#include "dbconnector.h"
#include "booldatamodelrus.h"
#include "monthdatamodel.h"
#include <qdebug.h>

QList <QString> DialogAddRow::getDataFromLineEdits(QList<QLineEdit*> lineEdits){
    QList <QString> list;
    for (QLineEdit *lineEdit : lineEdits) {
        list.push_back(lineEdit->text());
    }
    return list;
}

QList <QString> DialogAddRow::getDataFromcomboBoxes(QList<QComboBox*> comboBoxes){
    QList <QString> list;
    for (QComboBox *comboBox : comboBoxes) {
        QVariant data = comboBox->model()->data(comboBox->model()->index(comboBox->currentIndex(), 0));
        list.push_back(data.toString());
    }
    return list;
}

QList <QString> DialogAddRow::collectDataForQueryString(QWidget *parent){
    QList <QString> list=getDataFromLineEdits(parent->findChildren<QLineEdit*>());
    list+=getDataFromcomboBoxes(parent->findChildren<QComboBox*>());
    return list;
}

void DialogAddRow::setDataToLineEdits(QList<QLineEdit*> lineEdits, QVector <QString> &data){
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->setText(data[0]);
        data.pop_front();
    }
}

void DialogAddRow::setDataToDateEdits(QList<QDateEdit*> dateEdits, QVector <QString> &data){
    for (QDateEdit *dateEdit : dateEdits) {
        QDate date = QDate::fromString(data[0],"yyyy-MM-dd");
        dateEdit->setDate(date);
        data.pop_front();
    }
}

void DialogAddRow::setDataTocomboBoxes(QList<QComboBox*> comboBoxes, QVector <QString> &data){
    for (QComboBox *comboBox : comboBoxes) {
        comboBox->setCurrentText(data[0]);
        data.pop_front();
    }
}

void DialogAddRow::setDataToFields(QWidget *parent, QVector <QString> &data){
    setDataToDateEdits(parent->findChildren<QDateEdit*>(), data);
    setDataToLineEdits(parent->findChildren<QLineEdit*>(), data);
    setDataTocomboBoxes(parent->findChildren<QComboBox*>(), data);
}

void DialogAddRow::setFieldsDataContraints(){

    QStandardItemModel *boolModel=BoolDataModelRus::getModel();
    QStandardItemModel *monthModel=MonthDataModel::getModel();

    QSqlQueryModel *modelAddress = new QSqlQueryModel;
    modelAddress->setQuery("SELECT * from get_addresses()");

    QSqlQueryModel *modelUtilities = new QSqlQueryModel;
    modelUtilities->setQuery("select id_utility, \"Наименование услуги\" from utilities_info");

    QList<QComboBox*> comboBoxes=ui->stackedWidgetAddRow->findChildren<QComboBox*>();

    for(auto comboBox : comboBoxes){
        if(comboBox->objectName().contains("comboBoxAddress")){
            comboBox->setModel(modelAddress);
        }
        else if(comboBox->objectName().contains("comboBoxUtility")){
            comboBox->setModel(modelUtilities);
        }
        else if(comboBox->objectName().contains("comboBoxMeter")){
            comboBox->setModel(boolModel);
        }
        else if(comboBox->objectName().contains("comboBoxMonth")){
            comboBox->setModel(monthModel);
        }
        else if(comboBox->objectName().contains("comboBoxInclude")){
            comboBox->setModel(boolModel);
        }
        if (comboBox->model()->columnCount()>1) comboBox->setModelColumn(1);
    }
}

void DialogAddRow::updateSubComboBox(QComboBox *main, QComboBox *sub, QString field){
    QList<QComboBox*> comboBoxes;
    comboBoxes.append(main);
    QList <QString> data=getDataFromcomboBoxes(comboBoxes);
    QSqlQueryModel *modelApartmentNums = new QSqlQueryModel;
    QSqlQuery query{("select id_apartment, \"number\" from apartments where "+field+"="+data[0])};
    modelApartmentNums->setQuery(query);
    sub->setModel(modelApartmentNums);
    sub->setModelColumn(1);
}

DialogAddRow::DialogAddRow(int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRow)
{
    ui->setupUi(this);
    action="new";
    this->setWindowTitle("Новая запись ("+windowModTitles[index]+")");
    ui->stackedWidgetAddRow->setCurrentIndex(index);
    setFieldsDataContraints();
}

DialogAddRow::DialogAddRow(int index, QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRow)
{
    ui->setupUi(this);
    this->setWindowTitle("Новая запись ("+windowModTitles[index]+")");
    itemId2=id;
    ui->stackedWidgetAddRow->setCurrentIndex(index);
    setFieldsDataContraints();
}

DialogAddRow::DialogAddRow(int index, QVector <QString> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRow)
{
    ui->setupUi(this);
    action="edit";
    ui->stackedWidgetAddRow->setCurrentIndex(index);
    this->setWindowTitle("Изменение записи ("+windowModTitles[index]+")");
    setFieldsDataContraints();

    itemId=data[0];
    data.pop_front();

    setDataToFields(ui->stackedWidgetAddRow->currentWidget(), data);
}

DialogAddRow::~DialogAddRow()
{
    delete ui;
}

void DialogAddRow::on_buttonBox_accepted()
{
    QList <QString> list;
    QSqlQuery query;

    list = collectDataForQueryString(ui->stackedWidgetAddRow->currentWidget());

    if(!itemId.isEmpty()){
        list.push_front(itemId);
        query.prepare(updateQueryTemplates[ui->stackedWidgetAddRow->currentIndex()]);
        qDebug()<<updateQueryTemplates[ui->stackedWidgetAddRow->currentIndex()];
    }
    else if(!itemId2.isEmpty()){
        list.push_front(itemId2);
        qDebug()<<list[0]<<" id"<<addQueryTemplates[ui->stackedWidgetAddRow->currentIndex()];
        query.prepare(addQueryTemplates[ui->stackedWidgetAddRow->currentIndex()]);
    }
    else{
        query.prepare(addQueryTemplates[ui->stackedWidgetAddRow->currentIndex()]);
    }

    for(auto item : list){
        query.addBindValue(item);
        qDebug()<<item;
    }
    query.exec();
}

void DialogAddRow::on_comboBoxAddress_OF_currentIndexChanged(int index)
{
    updateSubComboBox(ui->comboBoxAddress_OF, ui->comboBoxApartmentNumber_OF,"id_building");
}

void DialogAddRow::on_comboBoxAddress_RF_currentIndexChanged(int index)
{
    updateSubComboBox(ui->comboBoxAddress_RF, ui->comboBoxApartmentNumber_RF,"id_building");
}


void DialogAddRow::on_comboBoxApartmentNumber_OF_currentIndexChanged(int index)
{
    qDebug()<<"Value of interest: "<<ui->doubleSpinBoxOwnershipInterest_OF->text()<<action;

    QList<QComboBox*> comboBoxes{ui->comboBoxApartmentNumber_OF};

    QSqlQuery query;
    query.prepare("select * from get_max_ownership_interest(?)");

    query.addBindValue(getDataFromcomboBoxes(comboBoxes)[0]);
    query.exec();
    query.next();
    ui->doubleSpinBoxOwnershipInterest_OF->setMaximum(ui->doubleSpinBoxOwnershipInterest_OF->text().toDouble()+(100-query.value(0).toDouble()));
    ui->doubleSpinBoxOwnershipInterest_OF->setValue(ui->doubleSpinBoxOwnershipInterest_OF->text().toDouble());
//    if(action=="new"){

//    ui->doubleSpinBoxOwnershipInterest_OF->setMaximum(100-query.value(0).toDouble());
//    }
//    else if (action=="edit" && 100-query.value(0).toDouble()>0){
//    ui->doubleSpinBoxOwnershipInterest_OF->setMaximum(100-ui->doubleSpinBoxOwnershipInterest_OF->text().toDouble());
//    }
//    else if (action=="edit"&& 100-query.value(0).toDouble()==0){
//    ui->doubleSpinBoxOwnershipInterest_OF->setMaximum(100-ui->doubleSpinBoxOwnershipInterest_OF->text().toDouble());
//    }
}

