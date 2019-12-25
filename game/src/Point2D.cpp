#include "Point2D.h"

#include <cmath>

Point2D::Point2D()
    : x(0.0f),y(0.0f)
{}

Point2D::Point2D(float nx, float ny)
    : x(nx),y(ny)
{}

Point2D::Point2D(const Point2D& other)
{
    x = other.x;
    y = other.y;
}

float Point2D::distance_to(Point2D& other)
{
    return sqrt( pow((x-other.x),2) + pow((y-other.y),2) );
}

std::string Point2D::to_string()
{
    return "[" + std::to_string(x) +
          ", " + std::to_string(y) + "]";
}
    
Point2D Point2D::operator+ (const Point2D& other)
{
    Point2D ret;
    ret.x = x + other.x;
    ret.y = y + other.y;
    return ret;
}
Point2D Point2D::operator- (const Point2D& other)
{
    Point2D ret;
    ret.x = x - other.x;
    ret.y = y - other.y;
    return ret;
}
void Point2D::operator= (const Point2D& other)
{
    x = other.x;
    y = other.y;
}
bool Point2D::operator== (const Point2D& other)
{
    return x==other.x && y == other.y;
}

