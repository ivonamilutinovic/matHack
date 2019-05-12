#include "board.h"
#include "figures/figure.h"
#include "figures/figure_types.h"

#include <vector>
#include <algorithm>

Board::Board(Color turn)
    : QGraphicsWidget(),
      m_turn{turn}
{
    /*for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            m_board[i][j] = nullptr;*/
}

Board::Board(const Board &other)
    : QGraphicsWidget(),
      m_turn{other.m_turn}
{
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            m_board[i][j] = other.m_board[i][j];
}

// copy-and-swap idiom - da bi operator dodele bio
// bezbedan prilikom pojave izuzetaka, obavezno je
// implementirati ga na ovaj nacin:
// 1. Pravi se privremena kopija objekta (poziva se
//    konstruktor kopije)
// 2. Zamene se sve clanske promenljive u *this i
//    privremenoj kopiji
Board& Board::operator=(const Board& other)
{
    auto temp = other;
    std::swap(m_board, temp.m_board);
    std::swap(m_turn, temp.m_turn);
    return *this;
}

Board& Board::operator=(Board&& other){

    std::swap(m_board, other.m_board);
    std::swap(m_turn, other.m_turn);
    return *this;
}

Board::Board(Board&& other)
    : Board()
{
    std::swap(m_board, other.m_board);
    std::swap(m_turn, other.m_turn);
}

void Board::add(const ptrFigure &fig, const Field & f) {
    m_board[f.rank() - 1][f.file() - 'a'] = fig;
}
void Board::remove(const Field & f) {
    m_board[f.rank() - 1][f.file() - 'a'].reset();
}

std::vector<Field> Board::pseudolegalMoves(const Field &f) const {
    if (Figure::isColor(m_board[f.rank() - 1][f.file() - 'a'], m_turn))
        return moves(f, false);
    return {};
}

Field Board::findKing(Color color) const
{
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (Figure::isColor(m_board[i][j], color) && dynamic_cast<const King *>(m_board[i][j].get()) != nullptr)
                return Field(i + 1, static_cast<char>(j + 'a'));
    throw std::runtime_error{"Nema kralja, care!"};
}

bool Board::isCheck(Color color) const
{
    Field king = findKing(color);
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (m_board[i][j] != nullptr && m_board[i][j]->color() != color)
            {
                std::vector<Field> fields = pseudolegalMoves(Field(i + 1, static_cast<char>(j + 'a')));
                if (std::find(fields.cbegin(), fields.cend(), king) != fields.cend())
                    return true;
            }
    return false;
}

std::vector<Field> Board::legalMoves(const Field &f) const
{
    if (Figure::isColor(m_board[f.rank() - 1][f.file() - 'a'], m_turn))
        return moves(f, true);
    return {};
}

std::vector<Field> Board::moves(const Field &f, bool legal) const
{
    ptrFigure fig = m_board[f.rank() - 1][f.file() - 'a'];
    std::vector<Field> fields;

    if (dynamic_cast<const Pawn*>(fig.get()) != nullptr) {
        if (fig->color() == Color::black && f.rank() > 1) {
            if (m_board[f.rank() - 2][f.file() - 'a'] == nullptr) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank() - 2][f.file() - 'a'] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() - 1, f.file());
                }
                else fields.emplace_back(f.rank() - 1, f.file());
                if (f.rank() == 7 && m_board[f.rank() - 3][f.file() - 'a'] == nullptr) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[f.rank() - 3][f.file() - 'a'] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(f.rank() - 2, f.file());
                    }
                    else fields.emplace_back(f.rank() - 2, f.file());
                }
            }
            if (f.file() > 'a' && Figure::isColor(m_board[f.rank() - 2][f.file() - 'a' - 1], Color::white)) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank() - 2][f.file() - 'a' - 1] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() - 1, f.file() - 1);
                }
                else fields.emplace_back(f.rank() - 1, f.file() - 1);
            }
            if (f.file() < 'h' && Figure::isColor(m_board[f.rank() - 2][f.file() - 'a' + 1], Color::white)) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank() - 2][f.file() - 'a' + 1] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() - 1, f.file() + 1);
                }
                else fields.emplace_back(f.rank() - 1, f.file() + 1);
            }
        } else if (fig->color() == Color::white && f.rank() < SIZE) {
            if (m_board[f.rank()][f.file() - 'a'] == nullptr) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank()][f.file() - 'a'] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() + 1, f.file());
                }
                else fields.emplace_back(f.rank() + 1, f.file());
                if (f.rank() == 2 && m_board[f.rank() + 1][f.file() - 'a'] == nullptr) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[f.rank() + 1][f.file() - 'a'] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(f.rank() + 2, f.file());
                    }
                    else fields.emplace_back(f.rank() + 2, f.file());
                }
            }
            if (f.file() > 'a' && Figure::isColor(m_board[f.rank()][f.file() - 'a' - 1], Color::black)) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank()][f.file() - 'a' - 1] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() + 1, f.file() - 1);
                }
                else fields.emplace_back(f.rank() + 1, f.file() - 1);
            }
            if (f.file() < 'h' && Figure::isColor(m_board[f.rank()][f.file() - 'a' + 1], Color::black)) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank()][f.file() - 'a' + 1] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() + 1, f.file() + 1);
                }
                else fields.emplace_back(f.rank() + 1, f.file() + 1);
            }
        }
    } else if (dynamic_cast<const Knight*>(fig.get()) != nullptr) {
        std::vector<Field> knightJump = f.knightJumpFields();
        for (const auto &field: knightJump) {
            int i = field.rank() - 1;
            int j = field.file() - 'a';
            if (!Figure::isColor(m_board[i][j], fig->color()))
            {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[i][j] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.push_back(field);
                }
                else fields.push_back(field);
            }
        }
    } else if (dynamic_cast<const King*>(fig.get()) != nullptr) {
        std::vector<Field> adjacent = f.adjacentFields();
        for (const Field &field: adjacent) {
            int i = field.rank() - 1;
            int j = field.file() - 'a';
            if (!Figure::isColor(m_board[i][j], fig->color()))
            {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[i][j] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                    temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                    if (!temp.isCheck(fig->color()))
                        fields.push_back(field);
                }
                else fields.push_back(field);
            }
        }
    } else {
        if (dynamic_cast<const Rook*>(fig.get()) != nullptr || dynamic_cast<const Queen*>(fig.get()) != nullptr) {
            /* proverava dokle moze da ide ulevo po tom redu */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') - 1; j >= 0; --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno po toj red */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') + 1; j < SIZE; ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;

            /* proverava dokle moze da ide nadole po toj liniji */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a'); i >= 0; --i)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide nagore po toj liniji */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a'); i < SIZE; ++i)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
        }
        if (dynamic_cast<const Bishop*>(fig.get()) != nullptr || dynamic_cast<const Queen*>(fig.get()) != nullptr) {
            /* proverava dokle moze da ide ulevo i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') - 1; i >=0 && j >= 0; --i, --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') + 1; i >= 0 && j < SIZE; --i, ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;

            /* proverava dokle moze da ide ulevo i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') - 1; i < SIZE && j >= 0; ++i, --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') + 1; i < SIZE && j < SIZE; ++i, ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        temp.m_turn = temp.m_turn == Color::white ? Color::black : Color::white;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
        }
    }
    return fields;
}

void Board::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *){

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            // postavaljmo boju polja u zavisnosti od pozicije
            if((i + j) % 2 == 0)
                painter->setBrush(QColor(142,113,193));
            else
                painter->setBrush(QColor(255,229,204));
            QRect rectangle = QRect(j*WIDTH, (7-i)*WIDTH, WIDTH, WIDTH);
            painter->drawRect(rectangle);


            // proveravamo o kojoj figuri je rec i koje je boje
            if(m_board[i][j] != nullptr){
                if(dynamic_cast<const Pawn*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_pawn.png"));
                else if(dynamic_cast<const Pawn*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_pawn.png"));
                else if(dynamic_cast<const King*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_king.png"));
                else if(dynamic_cast<const King*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_king.png"));
                else if(dynamic_cast<const Queen*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_queen.png"));
                else if(dynamic_cast<const Queen*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_queen.png"));
                else if(dynamic_cast<const Knight*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_knight.png"));
                else if(dynamic_cast<const Knight*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_knight.png"));
                else if(dynamic_cast<const Bishop*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_bishop.png"));
                else if(dynamic_cast<const Bishop*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_bishop.png"));
                else if(dynamic_cast<const Rook*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::black)
                    painter->drawImage(rectangle, QImage(":/images/black_rook.png"));
                else if(dynamic_cast<const Rook*>(m_board[i][j].get()) != nullptr
                        && m_board[i][j]->color() == Color::white)
                    painter->drawImage(rectangle, QImage(":/images/white_rook.png"));
            }
        }
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
            add(std::make_shared<Queen>(color), Field(string[2] - '0', string[1]));
            break;
        case 'k':
        case 'K':
            add(std::make_shared<King>(color), Field(string[2] - '0', string[1]));
            break;
        case 'b':
        case 'B':
            add(std::make_shared<Bishop>(color), Field(string[2] - '0', string[1]));
            break;
        case 'n':
        case 'N':
            add(std::make_shared<Knight>(color), Field(string[2] - '0', string[1]));
            break;
        case 'r':
        case 'R':
            add(std::make_shared<Rook>(color), Field(string[2] - '0', string[1]));
            break;
        case 'p':
        case 'P':
            add(std::make_shared<Pawn>(color), Field(string[2] - '0', string[1]));
            break;
        }
    }
}

const ptrFigure& Board::get(int rank, char file) const
{
    return m_board[rank - 1][static_cast<int>(file - 'a')];
}
