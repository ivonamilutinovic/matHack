#include "generator.h"
#include "ui_generator.h"
#include <iostream>
#include <fstream>
#include "figures/figure.h"
#include "figures/figure_types.h"
Generator::Generator(Board * board, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator), board(board)
{
    ui->setupUi(this);

    std::ifstream f{"board.txt"};
        board->read(f);

    scene.setSceneRect(6, 6, 517, 517);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    board->setPos(0,0);
    scene.addItem(board);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

void Board::read(std::istream &f)
{
    std::string string;
    while(f >> string)
    {
        Color color = std::islower(string[0]) ? Color::black : Color::white;
        switch (string.front())
        {
        case 'q':
        case 'Q':
            add(new Queen(color), Field(string[2] - '0', string[1]));
            break;
        case 'k':
        case 'K':
            add(new King(color), Field(string[2] - '0', string[1]));
            break;
        case 'b':
        case 'B':
            add(new Bishop(color), Field(string[2] - '0', string[1]));
            break;
        case 'n':
        case 'N':
            add(new Knight(color), Field(string[2] - '0', string[1]));
            break;
        case 'r':
        case 'R':
            add(new Rook(color), Field(string[2] - '0', string[1]));
            break;
        case 'p':
        case 'P':
            add(new Pawn(color), Field(string[2] - '0', string[1]));
            break;
        }
    }
}

Generator::~Generator()
{
    delete ui;
}
