#include "regress.h"
#include "ui_regress.h"
#include "math.h"
#include "iostream"
#include "cstdlib"

Regress::Regress(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Regress)
{
    //Seed rand().
    srand((unsigned)time(NULL));

    //Setup radio button id numbers.
    ui->setupUi(this);
    ui->polyGroup->setId(ui->firstOrder, 1);
    ui->polyGroup->setId(ui->secondOrder, 2);
    ui->polyGroup->setId(ui->thirdOrder, 3);
    ui->polyGroup->setId(ui->fourthOrder, 4);
    ui->polyGroup->setId(ui->fifthOrder, 5);
    ui->firstOrder->setChecked(true);

    //Setup regress settings table.
    ui->regressOptions->setColumnCount(3);
    ui->regressOptions->setColumnWidth(0, ui->regressOptions->width()/3);
    ui->regressOptions->setColumnWidth(1, ui->regressOptions->width()/3);
    ui->regressOptions->setColumnWidth(2, ui->regressOptions->width()/3);
    ui->regressOptions->setHorizontalHeaderItem(0, new QTableWidgetItem("Iterations"));
    ui->regressOptions->setHorizontalHeaderItem(1, new QTableWidgetItem("Batch Prob"));
    ui->regressOptions->setHorizontalHeaderItem(2, new QTableWidgetItem("Start Alpha"));
    ui->regressOptions->setRowCount(1);
    ui->regressOptions->verticalHeader()->setVisible(false);

    //Setup input table.
    //Setup Columns.
    ui->inputTable->setColumnCount(2);
    ui->inputTable->setColumnWidth(0, 164);
    ui->inputTable->setColumnWidth(1, 165);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("X components"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Y components"));

    //Setup Rows.
    ui->inputTable->setRowCount(8);

    ui->inputTable->horizontalHeaderItem(0)->setBackground(QBrush(QColor(200, 100, 100)));
    ui->inputTable->horizontalHeaderItem(1)->setBackground(QBrush(QColor(200, 100, 100)));


    //Setup Graph.
    ui->plotter->addGraph();
    ui->plotter->addGraph();
    ui->plotter->graph(0)->setScatterStyle(QCPScatterStyle::ssPlusCircle);
    ui->plotter->graph(0)->setScatterStyle(QCPScatterStyle::ssPlusCircle);

    QPen pen;
    pen.setColor(QColor(10, 10, 150));
    ui->plotter->graph(0)->setPen(pen);

    ui->plotter->graph(0)->setLineStyle(QCPGraph::lsNone);
}

Regress::~Regress()
{
    delete ui;
}


void Regress::on_Plot_clicked()
{
    inputX.clear();
    inputY.clear();
    int newX, newY;

    //Retrieve data from inputTable and store in Qvectors
    for(int i = 0; i < ui->inputTable->rowCount(); i++)
    {
        QTableWidgetItem *x = ui->inputTable->item(i, 0);
        QTableWidgetItem *y = ui->inputTable->item(i, 1);

        if(x && y)
        {
            newX = x->text().toDouble();
            newY = y->text().toDouble();

            inputX.append(newX);
            inputY.append(newY);

            //Find graph ranges.
            if(newX > xMax)
            {
                xMax = (int) ceil(newX);
            }
            else if(newX < xMin)
            {
                xMin = (int) floor(newX);
            }
            if(newY > yMax)
            {
                yMax = (int) ceil(newY);
            }
            else if(newY < yMin)
            {
                yMin = (int) floor(newY);
            }
        }
    }

    //Update Graph
    int addRoomX = (xMax - xMin)/8;
    int addRoomY = (yMax - yMin)/8;
    ui->plotter->xAxis->setRange(xMin - addRoomX, xMax + addRoomX);
    ui->plotter->yAxis->setRange(yMin - addRoomY, yMax + addRoomY);
    ui->plotter->graph(0)->setData(inputX, inputY);
    ui->plotter->replot();
    ui->plotter->update();
}

void Regress::on_polyFit_clicked()
{
    QTableWidgetItem *it = ui->regressOptions->item(0, 0);
    QTableWidgetItem *pr = ui->regressOptions->item(0, 1);
    QTableWidgetItem *al = ui->regressOptions->item(0, 2);

    if(it && pr && al)
    {
        numOfIterations = it->text().toDouble();
        probToChose = pr->text().toDouble();
        alpha = al->text().toDouble();
    }

    int polyID = ui->polyGroup->checkedId();
    switch (polyID)
    {
    case 1:
        break;
    case 2:
        secondOrderPolyFit();
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}

void Regress::on_addRow_clicked()
{
    ui->inputTable->insertRow(ui->inputTable->rowCount());
}

void Regress::on_removeRow_clicked()
{
    ui->inputTable->removeRow(ui->inputTable->rowCount() - 1);
}

void Regress::secondOrderPolyFit()
{
    fitX.clear();
    fitY.clear();

    // ax^2 + bx + c
    double a = 1.0, b = 0.0, c = 0.0;
    double aNew = 1.0, bNew = 0.0, cNew = 0.0;
    double aDir, bDir, cDir;
    double Err = 0.0, newErr = 0.0;
    int batchCount;

    //Initial mean squared error.
    for(int i = 0; i < inputX.length(); i++)
    {
        Err += pow(inputY.at(i) - (a * pow(inputX.at(i), 2) + b * inputX.at(i) + c), 2);
    }

    Err /= inputX.length();


    int count = 0;
    for(int i = 0; i < numOfIterations && count < 10000; i++)
    {
        batchCount = 0;
        newErr = 0.0;
        aDir = 0.0;
        bDir = 0.0;
        cDir = 0.0;

        for(int j = 0; j < inputX.length(); j++)
        {
            if(((double)rand())/((double)RAND_MAX) < probToChose)
            {
                batchCount++;
                aDir += 2 * pow(inputX.at(j), 2.0) * (inputY.at(j) - (a * pow(inputX.at(j), 2.0) + b * inputX.at(j) + c));
                bDir += 2 * inputX.at(j) * (inputY.at(j) - (a * pow(inputX.at(j), 2.0) + b * inputX.at(j) + c));
                cDir += 2 * (inputY.at(j) - (a * pow(inputX.at(j), 2.0) + b * inputX.at(j) + c));
            }
        }

        aDir /= batchCount;
        bDir /= batchCount;
        cDir /= batchCount;

        aNew += alpha * aDir;
        bNew += alpha * bDir;
        cNew += alpha * cDir;

        for(int j = 0; j < inputX.length(); j++)
        {
            newErr += pow(inputY.at(j) - (aNew * pow(inputX.at(j), 2) + bNew * inputX.at(j) + cNew), 2);
        }

        newErr /= inputX.length();

        if(true){
            a = aNew;
            b = bNew;
            c = cNew;
            Err = newErr;
        }else{
            count++;
            alpha *= 0.5;
        }
    }

    //Set X and Y values for polynomial.
    double xDiff = (xMax - xMin)/100.00;
    double currentX = (double) xMin;

    for(int i = 0; i < 100; i++)
    {
        fitX.append(currentX);
        fitY.append(a * pow(currentX, 2) + b * currentX + c);
        currentX += xDiff;
    }

    //Draw Second Graph.
    ui->plotter->graph(1)->setData(fitX, fitY);
    ui->plotter->replot();
    ui->plotter->update();

}




