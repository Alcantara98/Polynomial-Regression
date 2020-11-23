#ifndef REGRESS_H
#define REGRESS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Regress; }
QT_END_NAMESPACE

class Regress : public QMainWindow
{
    Q_OBJECT

public:
    Regress(QWidget *parent = nullptr);

    void secondOrderPolyFit();

    ~Regress();

private slots:
    void on_Plot_clicked();

    void on_addRow_clicked();

    void on_removeRow_clicked();

    void on_polyFit_clicked();

private:
    Ui::Regress *ui;
    QVector<double> inputX, inputY, fitX, fitY;
    int xMax= 5, yMax = 5, xMin = 0, yMin = 0;
    double probToChose, numOfIterations, alpha;
};
#endif // REGRESS_H
