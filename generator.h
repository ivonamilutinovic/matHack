#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>
#include <fstream>

#include "figures/figure.h"
#include "figures/figure_types.h"
#include "board.h"
#include "field.h"

namespace Ui {
class Generator;
}

class Generator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Generator(Board* board, QWidget *parent = nullptr);
    ~Generator();
    void smisliNaziv(Board* board);

private:
    Ui::Generator *ui;
    QGraphicsScene scene;
    Board *board;
};

#endif // GENERATOR_H
