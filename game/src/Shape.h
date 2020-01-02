#ifndef SHAPE_H
#define SHAPE_H value

#include "SDL.h"
#include "Point2D.h"
#include "Color.h"


class Shape
{
public:
    Shape(Point2D pos, Color color);
    virtual ~Shape() {}

    virtual void render(SDL_Renderer* renderer) = 0;
	
	Point2D get_position();
	Color get_color();

	void set_position(const Point2D& p);
	void set_color(const Color& p);

protected:
    Color color;
    Point2D position;
    bool alive = true;
};

#endif /* SHAPE_H */
