#ifndef MONTHDATAMODEL_H
#define MONTHDATAMODEL_H
#include <QStandardItemModel>
#include <QDate>

class MonthDataModel
{
private:
    inline static QStandardItemModel *monthModel=new QStandardItemModel(12,1);
public:
    MonthDataModel();
    static QStandardItemModel *getModel();
};

#endif // MONTHDATAMODEL_H
