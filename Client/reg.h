#ifndef REG_H
#define REG_H

#include <QDialog>

namespace Ui {
class Reg;
}

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);
    ~Reg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Reg *ui;
};

#endif // REG_H
