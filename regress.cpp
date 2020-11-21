#include "regress.h"
#include "ui_regress.h"
#include "math.h"

Regress::Regress(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Regress)
{
    //Setup radio button id numbers.
    ui->setupUi(this);
    ui->polyGroup->setId(ui->firstOrder, 1);
    ui->polyGroup->setId(ui->secondOrder, 2);
    ui->polyGroup->setId(ui->thirdOrder, 3);
    ui->polyGroup->setId(ui->fourthOrder, 4);
    ui->polyGroup->setId(ui->fifthOrder, 5);
    ui->firstOrder->setChecked(true);

    //Setup input table.
    //Setup Columns.
    ui->inputTable->setColumnCount(2);
    ui->inputTable->setColumnWidth(0, 175);
    ui->inputTable->setColumnWidth(1, 175);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("X components"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Y components"));

    //Setup Rows.
    ui->inputTable->setRowCount(8);
}

Regress::~Regress()
{
    delete ui;
}


void Regress::on_Plot_clicked()
{
    int polyType = ui->polyGroup->checkedId();
}
