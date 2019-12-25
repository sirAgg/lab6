#ifndef CIRCLE_H
#define CIRCLE_H value

#include "SDL.h"

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(Point2D pos, Color color, int radius);
    void render(SDL_Renderer* renderer);

	int get_radius();
	void set_radius(int r);
private:
    int radius;
};

#endif /* CIRCLE_H */

