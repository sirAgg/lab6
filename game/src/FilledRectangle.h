#ifndef __FILLEDRECTANGLE_H_
#define __FILLEDRECTANGLE_H_

#include "Rectangle.h"

class FilledRectangle: public Rectangle
{
public:
    FilledRectangle(Point2D pos, Color color, int width, int height);
    void render(SDL_Renderer* renderer);
};

#endif /* __FILLEDRECTANGLE_H_ */
