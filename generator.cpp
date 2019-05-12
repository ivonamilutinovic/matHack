#include "generator.h"
#include "ui_generator.h"
#include <iostream>
#include <fstream>
#include "figures/figure.h"
#include "figures/figure_types.h"
Generator::Generator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator),
    board()
{
    ui->setupUi(this);

    std::ifstream f{"board.txt"};
    board.read(f);

    auto legal = board.legalMoves(Field(1, 'd'));
    for (const auto &move: legal)
        std::cout << move << std::endl;

    scene.setSceneRect(6, 6, 516, 515);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    board.setPos(4,3);
    scene.addItem(&board);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

Generator::~Generator()
{
    delete ui;
}
