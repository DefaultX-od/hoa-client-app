#ifndef DIALOGADDROW_H
#define DIALOGADDROW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QComboBox>
#include <QDateEdit>

namespace Ui {
class DialogAddRow;
}

class DialogAddRow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddRow(int index, QWidget *parent = nullptr);
    explicit DialogAddRow(int index, QString id, QWidget *parent = nullptr);
    explicit DialogAddRow(int index, QVector <QString> data, QWidget *parent = nullptr);
    ~DialogAddRow();

private slots:
    void on_buttonBox_accepted();

    QList <QString> getDataFromLineEdits(QList<QLineEdit*> lineEdits);

    QList <QString> getDataFromcomboBoxes(QList<QComboBox*> comboBoxes);

    void setDataToFields(QWidget *parent, QVector <QString> &data);

    void setDataToLineEdits(QList<QLineEdit*> lineEdits, QVector <QString> &data);

    void setDataTocomboBoxes(QList<QComboBox*> comboBoxes, QVector <QString> &data);

    void setDataToDateEdits(QList<QDateEdit*> dateEdits, QVector <QString> &data);

    QList <QString> collectDataForQueryString(QWidget *parent);

    void setFieldsDataContraints();

    void updateSubComboBox(QComboBox *main, QComboBox *sub, QString str);

    void on_comboBoxAddress_OF_currentIndexChanged(int index);

    void on_comboBoxAddress_RF_currentIndexChanged(int index);

    void on_comboBoxApartmentNumber_OF_currentIndexChanged(int index);

private:
    QString itemId;
    QString itemId2;
    QString action;
    QList <QString> addQueryTemplates
        {
            "SELECT add_building(?, ?, ?, ?, ?)",
            "SELECT add_apartment(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            "SELECT add_owner(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            "SELECT add_receipt(?, ?, ?, ?, ?, ?)",
            "SELECT add_receipt_detail(?, ?, ?, ?)",
            "SELECT add_utility(?, ?, ?, ?)"
        };
    QList <QString> updateQueryTemplates
        {
            "SELECT update_building(?, ?, ?, ?, ?, ?)",
            "SELECT update_apartment(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            "SELECT update_owner(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            "SELECT update_receipt(?, ?, ?, ?, ?, ?, ?)",
            "SELECT update_receipt_detail(?, ?, ?, ?)",
            "SELECT update_utility(?, ?, ?, ?, ?)"
        };
    QList <QString> windowModTitles
    {
        "дом",
        "квартира",
        "собственник",
        "квитанция",
        "детали квитанции",
        "услуга"
    };

    Ui::DialogAddRow *ui;
};

#endif // DIALOGADDROW_H
