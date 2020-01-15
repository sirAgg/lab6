#ifndef __SEVENSEGSHAPE_H_
#define __NUMBERSHAPE_H_

#include "Shape.h"

class NumberShape : public Shape
{
public:
    NumberShape(Point2D pos, Color color, unsigned char lines, float scale);
    NumberShape(Point2D pos, Color color, int number, float scale);
    void render(SDL_Renderer *renderer) override;
    void set_number(int n);
    int get_number();

    void set_scale(float s);
private:
    unsigned char lines;
    float scale;
};

#endif // __NUMBERSHAPE_H_
