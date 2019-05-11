#include "generator.h"
#include <QApplication>
#include "board.h"
#include "figures/figure_types.h"
#include <iostream>
#include "generator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board *board = new Board();
    Generator w(board);
    w.show();

    return a.exec();
}
