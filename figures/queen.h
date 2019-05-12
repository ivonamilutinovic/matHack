#ifndef QUEEN_H
#define QUEEN_H

#include "figure.h"

class Queen: public Figure
{
public:
    Queen(Color color);
    ~Queen();
};

#endif // QUEEN_H
