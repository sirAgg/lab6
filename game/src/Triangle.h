#ifndef TRIANGLE
#define TRIANGLE value

#include "SDL.h"

#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(Point2D pos, Color color, int base, int height);
    void render(SDL_Renderer* renderer);
	int get_base();
	int get_height();
	void set_base(int b);
	void set_height(int h);
private:

    int base, height;

};


#endif /* TRIANGLE */
