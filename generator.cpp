#include "generator.h"
#include "ui_generator.h"

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

void smisliNaziv(Board* board){

   // nalazimo polje na kome se nalazi crni kralj
   Field blackKing = board->findKing(Color::black);
   // u allowedPosition nam se nalaze susedna polja za kralja
   std::vector<Field> allowedPosition = blackKing.adjacentFields();
   for(Field field: allowedPosition){
       if(board->get(field.rank(),field.file())->color() == Color::black){
           // proveravamo da li neka bela napada tu crnu

           // prolazimo kroz sve bele figure na tabli
           for(int i = 1; i < 9; i++)
                for(char j = 'a'; j < 'h' + 1; j++)
                    if(board->get(i,j)->color() == Color::white){

                        // zovemo metod legalMoves za sve bele figure kako bismo proverili
                        // da li neka bela napada crne koje su oko kralja
                        std::vector<Field> moves = board->legalMoves(Field(i,j));
                        // proveravamo da li legalMoves vraca polje koje je jednako poljima na kome se nalaze crne figure oko kralja
                        for(Field position : moves){

                            if(position == field){
                                //Dejan radi nesto
                            }
                        }

                    }
       }
   }

}


Generator::~Generator()
{
    delete ui;
}
