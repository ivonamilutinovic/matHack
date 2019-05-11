#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsWidget>
#include <QPainter>
#include <QStyleOption>
#include "figures/figure.h"
#include "field.h"
#include <memory>

#define WIDTH 65
#include <iostream>

class Board : public QGraphicsWidget
{
public:
    Board();
    ~Board() override;
    Board(const Board &other);
    Board& operator=(Board board);
    /* manipulacija table - postavljanje i skidanje figura */
    void add(const Figure * fig, const Field & f);
    void remove(const Field & f);
    /* funkcije */
    std::vector<Field> moves(const Field & f) const;
    void read(std::istream &f);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    std::vector<Field> pseudolegalMoves(const Field & f) const;
    Field findKing(Color color) const;
    bool isCheck(Color color) const; // isCheck(white) proverada da li je dat sah belom
    std::vector<Field> legalMoves(const Field &f) const;
    void free();
private:
   const Figure * m_board[8][8];
   std::vector<Field> moves(const Field & f, bool legal) const;
};

#endif // BOARD_H
