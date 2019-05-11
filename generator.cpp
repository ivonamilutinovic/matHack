#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);

    scene.setSceneRect(150, 150, 400, 400);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    board.setPos(0,0);
    scene.addItem(&board);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

Generator::~Generator()
{
    delete ui;
}
