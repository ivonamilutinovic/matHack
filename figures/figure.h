#ifndef FIGURE_H
#define FIGURE_H

#include "../color.h"

class Figure
{
public:
    Figure(Color m_color);
    virtual ~Figure() = 0;
    inline Color color() const { return m_color; }
    static bool isColor(const Figure * fig, Color color);
protected:
    Color m_color;
};

#endif // FIGURE_H
