#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

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
    explicit Generator(QWidget *parent = nullptr);
    ~Generator();
    std::vector<Field> smisliNaziv();//Board board, Board previousBoard1, Board previousBoard2, Board previousBoard3

private:
    Ui::Generator *ui;
    QGraphicsScene scene;
    Board board;
    Board previousBoard1;
    Board previousBoard2;
    Board previousBoard3;
};

#endif // GENERATOR_H
