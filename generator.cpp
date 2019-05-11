#include "generator.h"
#include "ui_generator.h"

Generator::Generator(Board * board, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator), board(board)
{
    ui->setupUi(this);

    std::ifstream f{"board.txt"};
        board->read(f);

    scene.setSceneRect(6, 6, 516, 515);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    board->setPos(4,3);
    scene.addItem(board);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

void smisliNaziv(Board* board){

   Field blackKing = board->findKing(Color::black);
   // u allowedPosition nam se nalaze susedna polja za kralja
   std::vector<Field> allowedPosition = blackKing.adjacentFields();
   for(Field field: allowedPosition){
       if(board->get(field.rank(),field.file())->isColor(Color::black)){
            // proveravamo da li neka bela napada tu crnu

       }
   }

}


Generator::~Generator()
{
    delete ui;
}
