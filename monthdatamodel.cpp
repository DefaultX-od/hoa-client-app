#include "monthdatamodel.h"
#include <QLocale>
MonthDataModel::MonthDataModel()
{
    QLocale locale(QLocale::system().language());

    for(int i=0; i<12; i++){
        monthModel->setItem(i, 0, new QStandardItem(QString::number(i+1)));
        monthModel->setItem(i, 1, new QStandardItem(locale.standaloneMonthName(i+1)));
    }
}

QStandardItemModel *MonthDataModel::getModel(){
    MonthDataModel model;
    return model.monthModel;
}
