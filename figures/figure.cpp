#include "figure.h"

Figure::Figure(Color color)
    : m_color(color)
{}

Figure::~Figure()
{}

bool Figure::isColor(const ptrFigure &fig, Color color) {
    return fig != nullptr && fig->color() == color;
}
