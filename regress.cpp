#include "regress.h"
#include "ui_regress.h"
#include "math.h"
#include "iostream"
#include "cstdlib"
#include "randomvaluesdialog.h"
#include "sharedData.h"
#include "string"

Regress::Regress(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Regress)
{
    //Don't Delete This!!!
    ui->setupUi(this);

    this->setWindowTitle("Polynomial Regression");
    //Set up degree box.
    ui->degreeBox->addItem("  Zeroth Degree");
    ui->degreeBox->addItem("  First Degree");
    ui->degreeBox->addItem("  Second Degree");
    ui->degreeBox->addItem("  Third Degree");
    ui->degreeBox->addItem("  Fourth Degree");
    ui->degreeBox->addItem("  Fifth Degree");
    ui->degreeBox->addItem("  Sixth Degree");
    ui->degreeBox->addItem("  Seventh Degree");
    ui->degreeBox->addItem("  Eigth Degree");
    ui->degreeBox->addItem("  Ninth Degree");
    ui->degreeBox->addItem("  Tenth Degree");

    //Set up addRowBox.
    ui->addRowBox->addItem("1");
    ui->addRowBox->addItem("5");
    ui->addRowBox->addItem("10");
    ui->addRowBox->addItem("50");
    ui->addRowBox->addItem("100");

    //Set up removeRowBox.
    ui->removeRowBox->addItem("1");
    ui->removeRowBox->addItem("5");
    ui->removeRowBox->addItem("10");
    ui->removeRowBox->addItem("50");
    ui->removeRowBox->addItem("100");

    //Setup input table.
    //Setup Columns.
    ui->inputTable->setColumnCount(2);
    ui->inputTable->setColumnWidth(0, 160);
    ui->inputTable->setColumnWidth(1, 160);
    ui->inputTable->setHorizontalHeaderItem(0, new QTableWidgetItem("X components"));
    ui->inputTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Y components"));

    //Setup Rows.
    ui->inputTable->setRowCount(10);

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

    xMax = 5;
    xMin = 5;
    yMax = 5;
    yMin = 5;

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
    int degree = ui->degreeBox->currentIndex();
    leastSquares(degree);
}

void Regress::on_addRow_clicked()
{
    int rowToAdd = ui->addRowBox->currentText().toInt();

    for(int i = 0; i < rowToAdd; i++)
    {
        ui->inputTable->insertRow(ui->inputTable->rowCount());
    }
}

void Regress::on_removeRow_clicked()
{
    int rowToRemove = ui->removeRowBox->currentText().toInt();
    for(int i = 0; i < rowToRemove; i++)
    {
        ui->inputTable->removeRow(ui->inputTable->rowCount() - 1);
    }
}

void Regress::leastSquares(int degree)
{
    fitX.clear();
    fitY.clear();

    double matrixValues[(2 * degree) + 1];
    double coef[degree + 1];
    double AMatrix[degree + 1][2 * (degree + 1)];
    double RVector[degree + 1];

    // Coeffecients = (AMatrix)^-1 . RVector

    //Calculate all the values to be placed in the A matrix
    //We can calculate it via matrix . matrix, but there is a lot of repeated digits.
    for(int i = 0; i < (2 * degree) + 1; i++)
    {
        matrixValues[i] = 0;
        for(int j = 0; j < inputX.length(); j++)
        {
            matrixValues[i] += pow(inputX.at(j), i);
        }
    }

    //Initialise the left hand side of the A matrix using the values we paced in matrixValues.
    for(int i = 0; i <= degree; i++)
    {
        for(int j = 0; j <= degree; j++)
        {
            AMatrix[i][j] = matrixValues[i + j];
        }
    }

    //Initialise the Right Vector.
    for(int i = 0; i <= degree; i++)
    {
        RVector[i]= 0;
        for(int j = 0; j < inputX.length(); j++)
        {
            RVector[i] += pow(inputX.at(j), i) * inputY.at(j);
        }
    }

    //Initialise the Identity Matrix in the right hand side of the AMatrix.
    for(int i = 0; i <= degree; i++)
    {
        for(int j = 0; j <= degree; j++)
        {
            if(i == j)
            {
                AMatrix[i][j + degree + 1] = 1;
            }
            else
            {
                AMatrix[i][j + degree + 1] = 0;
            }
        }
    }

    //Prints AMatrix to check if it is initiallized properly.
    //Test x = 1,2,5,6    y = 3,4,5,10
    //This should give an AMatrix:
    //  4  14
    //  14 66
    //    printf("\n");
    //    for (int h = 0; h <= degree; h++)
    //    {
    //        for (int p = 0; p < 2 * (degree + 1); p++)
    //        {
    //            printf("%0.3f\t", AMatrix[h][p]);
    //        }
    //        printf("\n");
    //    }

    //We can start Guass Jordan Elimination to find the inverse of AMatrix.
    double multiplier;

    //Turn every component to zero where indexes are not the same, i != j.
    for(int i = 0; i <= degree; i++)
    {
        for(int j = 0; j <= degree; j++)
        {
            if(i != j)
            {
                multiplier = AMatrix[j][i] / AMatrix[i][i];

                for(int k = i + 1; k < 2 * (degree + 1); k++)
                {
                    AMatrix[j][k] -= multiplier * AMatrix[i][k];
                }
            }
        }
    }

    //Divide the right hand side by the corresponding middle components (i == j).
    //After this, the right hand side should be the inverse matrix of the left hand side.
    for(int i = 0; i <= degree; i++)
    {
        for(int j = 0; j <= degree; j++)
        {
            AMatrix[i][j + degree + 1] /= AMatrix[i][i];
        }
    }

    //Finally, we can calculate the coefficients of the polynomial.
    for(int i = 0; i <= degree; i++)
    {
        coef[i] = 0;
        for(int j = 0; j <= degree; j++)
        {
            coef[i] += AMatrix[i][j + degree + 1] * RVector[j];
        }
    }

    //Set X and Y values for polynomial.
    int addRoomX = (xMax - xMin)/8;

    double xDiff = (xMax + addRoomX - (xMin - addRoomX))/200.00;
    double currentX = (double) xMin - addRoomX;
    double newY;
    for(int i = 0; i < 200; i++)
    {
        newY = 0;
        fitX.append(currentX);
        for(int j = 0; j <= degree; j++)
        {
            newY += coef[j] * pow(currentX, j);
        }
        fitY.append(newY);
        currentX += xDiff;
    }

    //Draw Second Graph.
    ui->plotter->graph(1)->setData(fitX, fitY);
    ui->plotter->replot();
    ui->plotter->update();
}

void Regress::on_randomValues_clicked()
{
    RandomValuesDialog randomValuesDialog;
    randomValuesDialog.setModal(true);
    randomValuesDialog.setSharedData(&this->myData);
    randomValuesDialog.exec();

    std::cout << "There";

    int numberOfValues = myData.getNumberOfVal();
    double *randomXValues = myData.getXValues();
    double *randomYValues = myData.getYValues();

    ui->inputTable->setRowCount(numberOfValues);

    for(int i = 0; i < numberOfValues; i++)
    {
        ui->inputTable->setItem(i, 0, new QTableWidgetItem(QString::number(randomXValues[i])));
        ui->inputTable->setItem(i, 1, new QTableWidgetItem(QString::number(randomYValues[i])));
    }
}
