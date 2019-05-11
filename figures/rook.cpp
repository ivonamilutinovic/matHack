#include "rook.h"

Rook::Rook(Color color)
    : Figure(color)
{
    std::cout << "constr Rook" << std::endl;
}

Rook::~Rook()
{
    std::cout << "destr Rook" << std::endl;
}
