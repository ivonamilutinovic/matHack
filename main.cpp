#include "generator.h"
#include <QApplication>
#include "board.h"
#include "figures/figure_types.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generator w;
    w.show();

    Board board;
    for (int j = 0; j < 8; ++j)
    {
        board.add(new Pawn(Color::white), Field(3, static_cast<char>('a' + j)));
        board.add(new Pawn(Color::black), Field(7, static_cast<char>('a' + j)));
    }
    board.add(new King(Color::white), Field(1, 'e'));
    board.add(new King(Color::black), Field(8, 'e'));
    board.add(new Queen(Color::white), Field(1, 'd'));
    board.add(new Queen(Color::black), Field(8, 'd'));
    board.add(new Bishop(Color::white), Field(1, 'f'));
    board.add(new Bishop(Color::black), Field(8, 'f'));
    board.add(new Bishop(Color::white), Field(1, 'c'));
    board.add(new Bishop(Color::black), Field(8, 'c'));
    board.add(new Knight(Color::white), Field(1, 'g'));
    board.add(new Knight(Color::black), Field(8, 'g'));
    board.add(new Knight(Color::white), Field(1, 'b'));
    board.add(new Knight(Color::black), Field(8, 'b'));
    board.add(new Rook(Color::white), Field(1, 'a'));
    board.add(new Rook(Color::black), Field(8, 'a'));
    board.add(new Rook(Color::white), Field(1, 'h'));
    board.add(new Rook(Color::black), Field(8, 'h'));
    auto fields = board.moves(Field(1, 'e'));
    for (const auto &field: fields)
        std::cout << field.file() << field.rank() << std::endl;
    return a.exec();
}
