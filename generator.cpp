#include "generator.h"
#include "ui_generator.h"
#include <cmath>

Generator::Generator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Generator),
    board()
{
    ui->setupUi(this);
    srand(time(nullptr));

//    std::ifstream f{"board.txt"};
//    board.read(f);
    generateCheckmate();

    /*auto legal = board.legalMoves(Field(1, 'd'));
    for (const auto &move: legal)
        std::cout << move << std::endl;*/

    scene.setSceneRect(6, 6, 516, 515);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    board.setPos(4,3);
    scene.addItem(&board);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
}

void Generator::generateCheckmate() {
    if (rand() % 2 == 0) {
        /* slucajna pozicija za crnog kralja - slucaj ivice table */
        // bez gubljenja opstosti, pretpostavimo da je kralj u vrsti 8 (crnoj bazi)
        // u nekim slucajevima, moze da bude na bilo kojoj ivici - tad su dozvoljena "rotiranja" itd
        bool bilo_gde = true;
        //std::vector<Field> dodatna_polja; // sta jos treba da se napada / brani (u slucaju bele figure na polju)
        int kralj_f = rand() % 6 + 1; // TODO ima i slucaj sa coskom !!
        board.add(std::make_shared<King>(Color::black), Field(8, kralj_f + 'a'));

        switch (rand() % /*10*/2) { // XXX TEST
        case 0: {
            /* samo kraljicom (+ odbrana kraljice) */
            int kraljica_f = kralj_f;
            board.add(std::make_shared<Queen>(Color::white), Field(7, kraljica_f + 'a'));

            // TODO TODO sada nam treba bela figura koja napada polje gde je kraljica (tj u ovom slucaju brani)
            break;
        }

        case 1: {
            /* kraljica + lovac */
            int kraljica_f = kralj_f + (rand() % 2 ? -1 : 1);
            board.add(std::make_shared<Queen>(Color::white), Field(6, kraljica_f + 'a'));
            int min_lovac = 0, max_lovac = 7;
            if (kraljica_f > kralj_f)
                max_lovac = kralj_f - 1;
            else
                min_lovac = kralj_f + 1;
            int lovac_f = rand() % (max_lovac - min_lovac + 1) + min_lovac;
            int razmak = abs(kralj_f - lovac_f);
            std::shared_ptr<Figure> newfig;
            if ((razmak == 1) && (rand() % 2))
                newfig = std::make_shared<Pawn>(Color::white);
            else
                newfig = std::make_shared<Bishop>(Color::white);
            board.add(newfig, Field(8 - razmak, lovac_f + 'a'));

            // TODO TODO bez ovog nece sve biti ispravno: ako je razmak == 1 -> TREBA NEKO DA GA BRANI
            break;
        }

        /*case 2: {
            //
        }*/
        }
    }

    else {
        /* potprogram slucaj 2 - na sred table (slozenija situacija za mat) */
        // TODO !!!
        generateCheckmate();
    }
}

std::vector<Field> Generator::smisliNaziv(/*Board board, Board previousBoard1, Board previousBoard2, Board previousBoard3*/) {
    std::vector<Field> array;

    // nalazimo polje na kome se nalazi crni kralj
    Field blackKing = board.findKing(Color::black);
    // u allowedPosition nam se nalaze susedna polja za kralja
    std::vector<Field> allowedPosition = blackKing.adjacentFields();
    for (Field field: allowedPosition) {
        if (Figure::isColor(board.get(field.rank(), field.file()), Color::black)) {
            // proveravamo da li neka bela napada tu crnu

            // prolazimo kroz sve bele figure na tabli
            for (int i = 1; i <= 8; i++)
                for (char j = 'a'; j <= 'h'; j++)
                    if (Figure::isColor(board.get(i, j), Color::white)) {
                        // zovemo metod legalMoves za sve bele figure kako bismo proverili
                        // da li neka bela napada crne koje su oko kralja
                        std::vector<Field> moves = board.legalMoves(Field(i, j));
                        // proveravamo da li legalMoves vraca polje koje je jednako poljima na kome se nalaze crne figure oko kralja
                        for (Field position : moves) {

                            if (position == field){
                                //Dejan radi nesto
                                array.push_back(position);
                            }
                        }
                    }
        }
    }
    return array;
}

Generator::~Generator()
{
    delete ui;
}
