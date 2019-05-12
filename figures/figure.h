#ifndef FIGURE_H
#define FIGURE_H

#include <memory>
#include <iostream>
#include "../color.h"

class Figure;
using ptrFigure = std::shared_ptr<Figure>;

class Figure
{
public:
    Figure(Color m_color);
    virtual ~Figure() = 0;
    inline Color color() const { return m_color; }
    static bool isColor(const ptrFigure &fig, Color color);
protected:
    Color m_color;
};

#endif // FIGURE_H
