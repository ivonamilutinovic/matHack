#include "figure.h"

Figure::Figure(Color color)
    : m_color(color)
{}

Figure::~Figure()
{}

bool Figure::isColor(const Figure *fig, Color color) {
    return fig != nullptr && fig->color() == color;
}

bool Figure::isColor(const std::shared_ptr<Figure> &fig, Color color) {
    return fig != nullptr && fig->color() == color;
}
