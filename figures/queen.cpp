#include "queen.h"

Queen::Queen(Color color)
    : Figure(color)
{
    std::cout << "constr Queen" << std::endl;
}

Queen::~Queen()
{
    std::cout << "destr Queen" << std::endl;
}
