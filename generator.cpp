#include "generator.h"
#include "ui_generator.h"
#include <cmath>
#include <QString>
#include <QDebug>

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
    bool bilo_gde = true;
    std::vector<Field> dodatna_polja; // sta jos treba da se napada / brani (u slucaju bele figure na polju)

//    if (rand() % 2 == 0) {
        /* slucajna pozicija za crnog kralja - slucaj ivice table */
        // bez gubljenja opstosti, pretpostavimo da je kralj u vrsti 8 (crnoj bazi)
        // u nekim slucajevima, moze da bude na bilo kojoj ivici - tad su dozvoljena "rotiranja" itd
        int kralj_f = rand() % 6 + 1; // TODO ima i slucaj sa coskom !!
        board.add(std::make_shared<King>(Color::black), Field(8, kralj_f + 'a'));

        switch (rand() % /*10*/2) { // XXX TEST
        case 0: {
            /* samo kraljicom (+ odbrana kraljice) */
            int kraljica_f = kralj_f;
            board.add(std::make_shared<Queen>(Color::white), Field(7, kraljica_f + 'a'));

            dodatna_polja.emplace_back(7, kraljica_f + 'a');
            break;
        }

        case 1: {
            /* kraljica + lovac */
            int kraljica_f = kralj_f + (rand() % 2 ? -1 : 1);
            board.add(std::make_shared<Queen>(Color::white), Field(6, kraljica_f + 'a'));

            if (rand() % 4 == 0) {
                /* specijalan slucaj topa pored kralja, umesto lovca - "Kill Box checkmate" */
                int top_f = (kraljica_f > kralj_f) ? kralj_f - 1 : kralj_f + 1;
                board.add(std::make_shared<Rook>(Color::white), Field(8, top_f + 'a'));
                break;
            }

            int min_lovac = 0, max_lovac = 7;
            if (kraljica_f > kralj_f)
                max_lovac = kralj_f - 1;
            else
                min_lovac = kralj_f + 1;
            int lovac_f = rand() % (max_lovac - min_lovac + 1) + min_lovac;
            int razmak = abs(kralj_f - lovac_f);
            std::shared_ptr<Figure> newfig;
            if ((razmak == 1) && (rand() % 2)) {
                newfig = std::make_shared<Pawn>(Color::white);
                bilo_gde = false; // zbog pesaka ne mozemo da premestimo gornju ivicu!
            } else
                newfig = std::make_shared<Bishop>(Color::white);
            board.add(newfig, Field(8 - razmak, lovac_f + 'a'));

            if (razmak == 1)
                dodatna_polja.emplace_back(8 - razmak, lovac_f + 'a');
            break;
        }

        case 2: {
            //
        }
        }
//    }

//    else {
        /* potprogram slucaj 2 - na sred table (slozenija situacija za mat) */
        // TODO !!!
//    }

    bool beliK = false;
    for (const Field & f : dodatna_polja) {
        std::vector<Field> napadaci_svi = board.findFields(f);
        std::vector<Field> napadaci;
        napadaci.reserve(napadaci_svi.size());
        std::copy_if(napadaci_svi.begin(), napadaci_svi.end(), std::back_inserter(napadaci),
                     [&](const auto & nf) { return board.get(nf.rank(), nf.file()) == nullptr; });
        unsigned long index = rand() % (napadaci.size() + 2);
        if (index >= napadaci.size()) {
            if (beliK)
                continue;
            /* UGLY MEGA TEST HACK - ovde cemo da turimo BELOG KRALJA, ni manje ni vise */
            // Pritom ovo NIJE UNIVERZALNO ispravno !! Za neke "templejte" bi moglo da SJEBE stvar!
            char bk_f;
            if (index == napadaci.size())
                // ide direktno ispod
                bk_f = f.file();
            else // ide pored - GDE, to moramo proveriti (ako je file == 'a' ili 'h' nemamo izbor)
            if (f.file() == 'a')
                bk_f = f.file() + 1; // 'b'
            else if (f.file() == 'h')
                bk_f = f.file() - 1; // 'g'
            else
                bk_f = (rand() % 2) ? f.file() - 1 : f.file() + 1;

            board.add(std::make_shared<King>(Color::white), Field(f.rank() - 1, bk_f));
            beliK = true;
        } else {
            /* Otkrij tip figure u odnosu na poziciju polja! */
            int razlX = napadaci[index].rank() - f.rank();
            int razlY = napadaci[index].file() - f.file();
            ptrFigure fig;

            if ((abs(razlX) == 1 && abs(razlY) == 2) || (abs(razlX) == 2 && abs(razlY) == 1))
                fig = std::make_shared<Knight>(Color::white);
            else if (abs(razlX) == abs(razlY) && razlX) {
                fig = std::make_shared<Bishop>(Color::white);
            }
            else if ((!razlX && razlY) || (razlX && !razlY))
                fig = std::make_shared<Rook>(Color::white);

            if (fig.get() != nullptr)
                board.add(fig, napadaci[index]);
            else qDebug() << QString(
                "Za odbranu / napad polja %1%2 dobio sam da postavim figuru na polje %3%4 sto izgleda pogresno !!"
                ).arg(f.file()).arg(f.rank()).arg(napadaci[index].file()).arg(napadaci[index].rank());
        }
    }

    /* TODO TODO - sitne izmene ? */

    /* TODO TODO - rotacije (u slucaju bilo_gde), mirror */

    /* TODO - dodavanje ostalih figura koje ne kvare mat */
    /* TODO TODO - postavljanje BELOG KRALJA (moze zajedno sa dodavanjem ostalih figura) */
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
