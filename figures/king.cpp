#include "king.h"

King::King(Color color)
    : Figure(color)
{
    std::cout << "constr King" << std::endl;
}

King::~King()
{
    std::cout << "destr King" << std::endl;
}
