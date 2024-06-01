#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int idReceipt;

private slots:
    void on_pushButtonEditRow_clicked();

    void on_comboBoxTableSelect_currentIndexChanged(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButtonAddRow_clicked();

    void setDataEditState(bool state);

    void tableViewUpdate();

    void on_comboBoxStateSelect_currentTextChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void setFiltersDataConstraints();

    void on_comboBoxAddressSelect_A_currentTextChanged(const QString &arg1);

    void on_pushButtonRemoveRow_clicked();

    void on_comboBoxCitySelect_currentTextChanged(const QString &arg1);


    void on_comboBoxPeriodSelect__currentTextChanged(const QString &arg1);

    void on_comboBoxPeriodSelect_1_currentTextChanged(const QString &arg1);

    void on_comboBoxAddressSelect_O_currentTextChanged(const QString &arg1);

private:
    QString tableQuery;
    QString filterQuery;
    QList <QString> valuesToBind;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
