#ifndef DIALOGCONFIRMATION_H
#define DIALOGCONFIRMATION_H

#include <QDialog>

namespace Ui {
class DialogConfirmation;
}

class DialogConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfirmation(QWidget *parent = nullptr);
    ~DialogConfirmation();

private:
    Ui::DialogConfirmation *ui;
};

#endif // DIALOGCONFIRMATION_H
