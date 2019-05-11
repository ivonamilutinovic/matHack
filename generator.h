#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>

namespace Ui {
class Generator;
}

class Generator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = nullptr);
    ~Generator();

private:
    Ui::Generator *ui;
};

#endif // GENERATOR_H
