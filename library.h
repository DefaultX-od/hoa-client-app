#ifndef LIBRARY_H
#define LIBRARY_H

#include <QStandardItemModel>

class library
{
private:
    inline static QList <QString> mainQueryList{
        "select * from buildings_info",
        "select * from apartments_info",
        "select * from owners_info",
        "select * from receipts_info",
        "select * from meter_data_info",
        "select * from utilities_info"
    };

    inline static QList <QString> itemQueryList{
        "SELECT * from get_building(?)",
        "SELECT * from get_apartment(?)",
        "SELECT * from get_owner(?)",
        "SELECT * from get_receipt(?)",
        "SELECT * from get_receipt_detail(?)",
        "SELECT * from get_utility(?)"
    };
    inline static QList <QString> deleteQueryList{
        "SELECT delete_building(?)",
        "SELECT delete_apartment(?)",
        "SELECT delete_owner(?)",
        "SELECT delete_receipt(?)",
        "SELECT delete_receipt_detail(?)",
        "SELECT delete_utility(?)"
    };

    inline static QString filterState{"select * from buildings_info where \"Страна\"=?"};
    inline static QString filterCity{"select * from buildings_info where \"Страна\"=? and \"Город\"=?"};
    inline static QString filterAddressApartments{"select * from apartments_info where \"Адрес\"=?"};
    inline static QString filterAddressOwners{"select * from owners_info where \"Адрес\"=?"};
    inline static QString filterPeriodReceipts{"select * from receipts_info where \"Период месяц\"::text||', '||\"Период год\"::text=?"};
    inline static QString filterPeriodMeterData{"select * from meter_data_info where \"Период месяц\"::text||', '||\"Период год\"::text=?"};

public:
    library();
    inline static QString getMainQuery(int index){
        return mainQueryList[index];
    }
    inline static QString getItemQuery(int index){
        return itemQueryList[index];
    }
    inline static QString getDeleteItemQuery(int index){
        return deleteQueryList[index];
    }
    inline static QString getFilterState(){
        return filterState;
    }
    inline static QString getFilterCity(){
        return filterCity;
    }
    inline static QString getFilterAddressApartments(){
        return filterAddressApartments;
    }
    inline static QString getFilterAddressOwners(){
        return filterAddressOwners;
    }
    inline static QString getFilterPeriodReceipts(){
        return filterPeriodReceipts;
    }
    inline static QString getFilterPeriodMeterData(){
        return filterPeriodMeterData;
    }
};

#endif // LIBRARY_H
