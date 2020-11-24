#ifndef RANDOMVALUESDIALOG_H
#define RANDOMVALUESDIALOG_H
#include "regress.h"
#include "sharedData.h"

#include <QDialog>

namespace Ui {
class RandomValuesDialog;
}

class RandomValuesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RandomValuesDialog(QWidget *parent = nullptr);
    ~RandomValuesDialog();
    void setSharedData(SharedData *sharedData);

private slots:
    void on_generateValues_clicked();

private:
    Ui::RandomValuesDialog *ui;
    SharedData *myData;
};

#endif // RANDOMVALUESDIALOG_H
