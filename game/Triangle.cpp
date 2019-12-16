#include "Triangle.h"

#include <stdio.h>


Triangle::Triangle(Point2D pos, Color color, int base, int height)
    : Shape(pos,color), base(base), height(height)
{}

void Triangle::render(SDL_Renderer* renderer)
{
    printf("TRIANGLE:\n\tpos: %s\n\tcolor: %08X\n\tbase: %d\n\theight: %d\n",
         position.to_string().c_str(), color.toInt(), base, height );
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int hb = base/2;
    int hh = height/2;
    SDL_RenderDrawLine(renderer, position.get_x()-hb, position.get_y()+hh, position.get_x()+hb, position.get_y()+hh );
    SDL_RenderDrawLine(renderer, position.get_x()-hb, position.get_y()+hh, position.get_x()   , position.get_y()-hh );
    SDL_RenderDrawLine(renderer, position.get_x()+hb, position.get_y()+hh, position.get_x()   , position.get_y()-hh );
}

int Triangle::get_base() { return base; }
int Triangle::get_height() { return height; }
void Triangle::set_base(int b) { base = b; }
void Triangle::set_height(int h) { height = h; }
