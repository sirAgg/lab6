#include "Shape.h"

Shape::Shape(Point2D pos, Color color)
    : color(color)
{
    position = pos;
}

Point2D Shape::get_position() { return position;  }
Color Shape::get_color() { return color; }

void Shape::set_position(const Point2D& p) { position = p; }
void Shape::set_color(const Color& p) { color = p; }