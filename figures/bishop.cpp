#include "bishop.h"

Bishop::Bishop(Color color)
    : Figure(color)
{
    std::cout << "constr Bishop" << std::endl;
}

Bishop::~Bishop()
{
    std::cout << "destr Bishop" << std::endl;
}
