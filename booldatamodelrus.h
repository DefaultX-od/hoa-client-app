#ifndef BOOLDATAMODELRUS_H
#define BOOLDATAMODELRUS_H

#include <QStandardItemModel>

class BoolDataModelRus
{
private:
    inline static QStandardItemModel *boolModel=new QStandardItemModel(1,1);

public:
    BoolDataModelRus();
    static QStandardItemModel *getModel();
};

#endif // BOOLDATAMODELRUS_H
