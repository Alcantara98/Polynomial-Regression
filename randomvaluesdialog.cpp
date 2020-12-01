#include "randomvaluesdialog.h"
#include "ui_randomvaluesdialog.h"
#include "iostream"

RandomValuesDialog::RandomValuesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomValuesDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Random Values");
    this->setWindowIcon(QIcon(":/regress.ico"));

    ui->minXValueLineEdit->setText("0");
    ui->maxXValueLineEdit->setText("40");
    ui->minYValueLineEdit->setText("0");
    ui->maxYValueLineEdit->setText("50");
    ui->amountLineEdit->setText("15");

//    ui->generateValues->setFixedHeight(60);
//    ui->generateLabel->setFixedHeight(50);
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
    myData->setGenerate(true);
    ui->generateLabel->setText("Values have been generated!!! \nPlease close the window.");

    double xMin, xMax, yMin, yMax;
    int numberOfValues;

    if(ui->amountLineEdit->text().isEmpty()){
        numberOfValues = 15;
    }else{
        numberOfValues = ui->amountLineEdit->text().toInt();
    }

    if(ui->minXValueLineEdit->text().isEmpty()){
        xMin = 0;
    }else{
        xMin = ui->minXValueLineEdit->text().toDouble();
    }

    if(ui->maxXValueLineEdit->text().isEmpty()){
        xMax = 40;
    }else{
        xMax = ui->maxXValueLineEdit->text().toDouble();
    }

    if(ui->minYValueLabel->text().isEmpty()){
        yMin = 0;
    }else{
        yMin = ui->minYValueLabel->text().toDouble();
    }

    if(ui->maxYValueLabel->text().isEmpty()){
        yMax = 50;
    }else{
        yMax = ui->maxYValueLineEdit->text().toDouble();
    }

    myData->generateValues(numberOfValues, xMin, xMax, yMin, yMax);
}
