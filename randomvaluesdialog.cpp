#include "randomvaluesdialog.h"
#include "ui_randomvaluesdialog.h"
#include "iostream"

RandomValuesDialog::RandomValuesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomValuesDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Random Values");
}

RandomValuesDialog::~RandomValuesDialog()
{
    delete ui;
}

void RandomValuesDialog::setSharedData(SharedData *sharedData)
{
    this->myData = sharedData;
}

void RandomValuesDialog::on_generateValues_clicked()
{
    double xMin, xMax, yMin, yMax;
    int numberOfValues;

    if(ui->numberOfValues->toPlainText().isEmpty()){
        numberOfValues = 15;
    }else{
        numberOfValues = ui->numberOfValues->toPlainText().toInt();
    }

    if(ui->xMinInput->toPlainText().isEmpty()){
        xMin = 0;
    }else{
        xMin = ui->xMinInput->toPlainText().toDouble();
    }

    if(ui->xMaxInput->toPlainText().isEmpty()){
        xMax = 40;
    }else{
        xMax = ui->xMaxInput->toPlainText().toDouble();
    }

    if(ui->yMinInput->toPlainText().isEmpty()){
        yMin = 0;
    }else{
        yMin = ui->yMinInput->toPlainText().toDouble();
    }

    if(ui->yMaxInput->toPlainText().isEmpty()){
        yMax = 50;
    }else{
        yMax = ui->yMaxInput->toPlainText().toDouble();
    }

    myData->generateValues(numberOfValues, xMin, xMax, yMin, yMax);
    std::cout << "Hello";
}
