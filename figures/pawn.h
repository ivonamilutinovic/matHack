#ifndef PAWN_H
#define PAWN_H

#include "figure.h"

class Pawn: public Figure
{
public:
    Pawn(Color color);
    ~Pawn();
};

#endif // PAWN_H
