#include "pawn.h"

Pawn::Pawn(Color color)
    : Figure(color)
{
    std::cout << "constr Pawn" << std::endl;
}

Pawn::~Pawn()
{
    std::cout << "destr Pawn" << std::endl;
}
