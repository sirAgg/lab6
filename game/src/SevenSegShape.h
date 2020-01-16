#ifndef __SEVENSEGSHAPE_H_
#define __SEVENSEGSHAPE_H_

#include "Shape.h"

class SevenSegShape : public Shape
{
public:
    SevenSegShape(Point2D pos, Color color, unsigned char lines, float scale);
    SevenSegShape(Point2D pos, Color color, int number, float scale);
    void render(SDL_Renderer *renderer) override;
    void set_number(int n);
    void set_lines(unsigned char l);

    void set_scale(float s);
private:
    unsigned char lines;
    float scale;
};

#endif // __SEVENSEGSHAPE_H_
