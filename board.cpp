#include "board.h"
#include "figures/figure.h"
#include "figures/figure_types.h"

#include <vector>
#include <algorithm>
#include <sstream>

Board::Board()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            m_board[i][j] = nullptr;
}

void Board::add(const Figure * fig, const Field & f) {
    m_board[f.rank() - 1][f.file() - 'a'] = fig;
}
void Board::remove(const Field & f) {
    delete m_board[f.rank() - 1][f.file() - 'a'];
    m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
}

std::vector<Field> Board::pseudolegalMoves(const Field &f) const {
    return moves(f, false);
}

Field Board::findKing(Color color) const
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (Figure::isColor(m_board[i][j], color) && dynamic_cast<const King *>(m_board[i][j]) != nullptr)
                return Field(i + 1, static_cast<char>(j + 'a'));
    throw std::runtime_error{"Nema kralja, care!"};
}

bool Board::isCheck(Color color) const
{
    Field king = findKing(color);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
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
    return moves(f, true);
}

std::vector<Field> Board::moves(const Field &f, bool legal) const
{
    const Figure *fig = m_board[f.rank() - 1][f.file() - 'a'];
    std::vector<Field> fields;

    if (dynamic_cast<const Pawn*>(fig) != nullptr) {
        if (fig->color() == Color::black && f.rank() > 1) {
            if (m_board[f.rank() - 2][f.file() - 'a'] == nullptr) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank() - 2][f.file() - 'a'] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
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
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() - 1, f.file() + 1);
                }
                else fields.emplace_back(f.rank() - 1, f.file() + 1);
            }
        } else if (fig->color() == Color::white && f.rank() < 8) {
            if (m_board[f.rank()][f.file() - 'a'] == nullptr) {
                if (legal)
                {
                    Board temp = *this; // plitko kopiranje
                    temp.m_board[f.rank()][f.file() - 'a'] = fig;
                    temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
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
                    if (!temp.isCheck(fig->color()))
                        fields.emplace_back(f.rank() + 1, f.file() + 1);
                }
                else fields.emplace_back(f.rank() + 1, f.file() + 1);
            }
        }
    } else if (dynamic_cast<const Knight*>(fig) != nullptr) {
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
                    if (!temp.isCheck(fig->color()))
                        fields.push_back(field);
                }
                else fields.push_back(field);
            }
        }
    } else if (dynamic_cast<const King*>(fig) != nullptr) {
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
                    if (!temp.isCheck(fig->color()))
                        fields.push_back(field);
                }
                else fields.push_back(field);
            }
        }
    } else {
        if (dynamic_cast<const Rook*>(fig) != nullptr || dynamic_cast<const Queen*>(fig) != nullptr) {
            /* proverava dokle moze da ide ulevo po tom redu */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') - 1; j >= 0; --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno po toj red */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') + 1; j < 8; ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
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
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide nagore po toj liniji */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a'); i < 8; ++i)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
        }
        if (dynamic_cast<const Bishop*>(fig) != nullptr || dynamic_cast<const Queen*>(fig) != nullptr) {
            /* proverava dokle moze da ide ulevo i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') - 1; i >=0 && j >= 0; --i, --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') + 1; i >= 0 && j < 8; --i, ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;

            /* proverava dokle moze da ide ulevo i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') - 1; i < 8 && j >= 0; ++i, --j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
                        if (!temp.isCheck(fig->color()))
                            fields.emplace_back(i + 1, j + 'a');
                    }
                    else fields.emplace_back(i + 1, j + 'a');
                    if (m_board[i][j] != nullptr)
                        break;
                }
                else break;
            /* proverava dokle moze da ide udesno i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') + 1; i < 8 && j < 8; ++i, ++j)
                if (!Figure::isColor(m_board[i][j], fig->color())) {
                    if (legal)
                    {
                        Board temp = *this; // plitko kopiranje
                        temp.m_board[i][j] = fig;
                        temp.m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
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
