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
    ~Regress();

private slots:
    void on_Plot_clicked();

private:
    Ui::Regress *ui;
};
#endif // REGRESS_H
