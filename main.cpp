#include "generator.h"
#include <QApplication>
#include "board.h"
#include "figures/figure_types.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generator w;
    w.show();

    Board board;
    std::ifstream f{"board.txt"};
    board.read(f);
    auto fields = board.legalMoves(Field(1, 'd'));
    for (const auto &field: fields)
        std::cout << field.file() << field.rank() << std::endl;
    return a.exec();
}
