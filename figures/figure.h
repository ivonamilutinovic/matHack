#ifndef FIGURE_H
#define FIGURE_H

#include "../color.h"

class Figure
{
public:
    Figure(Color m_color);
    virtual ~Figure() = 0;
protected:
    Color m_color;
};

#endif // FIGURE_H
