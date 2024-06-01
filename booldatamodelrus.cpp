#include "booldatamodelrus.h"

BoolDataModelRus::BoolDataModelRus()
{
    boolModel->setItem(0, 0, new QStandardItem(QString("false")));
    boolModel->setItem(0, 1, new QStandardItem(QString("нет")));
    boolModel->setItem(1, 0, new QStandardItem(QString("true")));
    boolModel->setItem(1, 1, new QStandardItem(QString("да")));
}
QStandardItemModel *BoolDataModelRus::getModel(){
    BoolDataModelRus model;
    return model.boolModel;
}
