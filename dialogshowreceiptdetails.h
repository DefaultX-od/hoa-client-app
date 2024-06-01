#ifndef DIALOGSHOWRECEIPTDETAILS_H
#define DIALOGSHOWRECEIPTDETAILS_H

#include <QDialog>

namespace Ui {
class DialogShowReceiptDetails;
}

class DialogShowReceiptDetails : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShowReceiptDetails(int idReceipt, QWidget *parent = nullptr);
    ~DialogShowReceiptDetails();

private slots:
    void on_pushButtonAddRow_clicked();
    void tableViewUpdate();

    void on_pushButtonEditRow_clicked();

    void on_pushButtonRemoveRow_clicked();

private:
    Ui::DialogShowReceiptDetails *ui;
    int id;
};

#endif // DIALOGSHOWRECEIPTDETAILS_H
