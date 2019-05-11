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

Generator::~Generator()
{
    delete ui;
}
