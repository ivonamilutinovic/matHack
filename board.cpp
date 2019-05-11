#include "board.h"
#include <vector>
#include "figures/figure.h"
#include "figures/figure_types.h"

Board::Board()
{

}

void Board::add(const Figure * fig, const Field & f) {
    m_board[f.rank() - 1][f.file() - 'a'] = fig;
}
void Board::remove(const Field & f) {
    delete m_board[f.rank() - 1][f.file() - 'a'];
    m_board[f.rank() - 1][f.file() - 'a'] = nullptr;
}

std::vector<Field> Board::moves(const Field &f) const {
    const Figure *fig = m_board[f.rank() - 1][f.file() - 'a'];
    std::vector<Field> fields;

    if (dynamic_cast<const Pawn*>(fig) != nullptr) {
        if (fig->color() == Color::black && f.rank() > 1) {
            if (m_board[f.rank() - 2][f.file() - 'a'] == nullptr) {
                fields.emplace_back(f.rank() - 2, f.file() - 'a');
                if (f.rank() == 7 && m_board[f.rank() - 3][f.file() - 'a'] == nullptr)
                    fields.emplace_back(f.rank() - 3, f.file() - 'a');
            }
            if (f.file() > 'a' && Figure::isColor(m_board[f.rank() - 2][f.file() - 'a' - 1], Color::white))
                fields.emplace_back(f.rank() - 2, f.file() - 'a' - 1);
            if (f.file() < 'h' && Figure::isColor(m_board[f.rank() - 2][f.file() - 'a' + 1], Color::white))
                fields.emplace_back(f.rank() - 2, f.file() - 'a' + 1);
        } else if (fig->color() == Color::white && f.rank() < 8) {
            if (m_board[f.rank()][f.file() - 'a'] == nullptr) {
                fields.emplace_back(f.rank(), f.file() - 'a');
                if (f.rank() == 2 && m_board[f.rank() + 1][f.file() - 'a'] == nullptr)
                    fields.emplace_back(f.rank() + 1, f.file() - 'a');
            }
            if (f.file() > 'a' && Figure::isColor(m_board[f.rank()][f.file() - 'a' - 1], Color::black))
                fields.emplace_back(f.rank(), f.file() - 'a' - 1);
            if (f.file() < 'h' && Figure::isColor(m_board[f.rank()][f.file() - 'a' + 1], Color::black))
                fields.emplace_back(f.rank(), f.file() - 'a' + 1);
        }
    } else if (dynamic_cast<const Knight*>(fig) != nullptr) {
        std::vector<Field> knightJump = f.knightJumpFields();
        for (const auto &field: knightJump) {
            int i = field.rank() - 1;
            int j = field.file() - 'a';
            // TODO sve ispod moze da se prepravi na !Figure::isColor(...)
            if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                fields.push_back(field);
        }
    } else if (dynamic_cast<const King*>(fig) != nullptr) {
        std::vector<Field> adjacent = f.adjacentFields();
        for (const Field &field: adjacent) {
            int i = field.rank() - 1;
            int j = field.file() - 'a';
            if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                fields.push_back(field);
        }
    } else {
        if (dynamic_cast<const Rook*>(fig) != nullptr || dynamic_cast<const Queen*>(fig) != nullptr) {
            /* proverava dokle moze da ide ulevo po tom redu */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') - 1; j >= 0; --j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
            /* proverava dokle moze da ide udesno po toj red */
            for (int i = f.rank() - 1, j = static_cast<int>(f.file() - 'a') + 1; j < 8; ++j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;

            /* proverava dokle moze da ide nadole po toj liniji */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a'); i >= 0; --i)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
            /* proverava dokle moze da ide nagore po toj liniji */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a'); i < 8; ++i)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
        }
        if (dynamic_cast<const Bishop*>(fig) != nullptr || dynamic_cast<const Queen*>(fig) != nullptr) {
            /* proverava dokle moze da ide ulevo i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') - 1; i >=0 && j >= 0; --i, --j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
            /* proverava dokle moze da ide udesno i nadole po dijagonali */
            for (int i = f.rank() - 2, j = static_cast<int>(f.file() - 'a') + 1; i >= 0 && j < 8; --i, ++j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;

            /* proverava dokle moze da ide ulevo i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') - 1; i < 8 && j >= 0; ++i, --j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
            /* proverava dokle moze da ide udesno i nagore po dijagonali */
            for (int i = f.rank(), j = static_cast<int>(f.file() - 'a') + 1; i < 8 && j < 8; ++i, ++j)
                if (m_board[i][j] == nullptr || fig->color() != m_board[i][j]->color())
                    fields.emplace_back(i + 1, j + 'a');
                else break;
        }
    }
    return fields;
}
