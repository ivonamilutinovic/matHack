#include "knight.h"

Knight::Knight(Color color)
    : Figure(color)
{
    std::cout << "constr Knight" << std::endl;
}

Knight::~Knight()
{
    std::cout << "destr Knight" << std::endl;
}
