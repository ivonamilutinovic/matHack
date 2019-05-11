#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsWidget>
#include <QPainter>
#include <QStyleOption>
#include "figures/figure.h"
#include "field.h"
#include <memory>
#include "figures/figure.h"
#include <memory>

#define WIDTH 65
#define LINE_WIDTH 1

class Board : public QGraphicsWidget
{
public:
    Board();
    /* manipulacija table - postavljanje i skidanje figura */
    void add(const Figure * fig, const Field & f);
    void remove(const Field & f);
    Board(const Board &other);
    Board& operator=(Board board);
    /* funkcije */
    std::vector<Field> moves(const Field & f) const;
    void read(std::istream &f);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;




private:
   const Figure * m_board[8][8];
};

#endif // BOARD_H
