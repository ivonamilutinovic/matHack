#ifndef BOARD_H
#define BOARD_H

#include "figures/figure.h"
#include "field.h"
#include <memory>

class Board
{
public:
    Board();
    /* manipulacija table - postavljanje i skidanje figura */
    void add(const Figure * fig, const Field & f);
    void remove(const Field & f);
    /* funkcije */
    std::vector<Field> moves(const Field & f) const;

private:
   const Figure * m_board[8][8];
};

#endif // BOARD_H
