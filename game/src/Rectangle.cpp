#include "Rectangle.h"
#include <stdio.h>

Rectangle::Rectangle(Point2D pos, Color color, int width, int height)
    : Shape(pos,color), width(width), height(height)
{}

void Rectangle::render(SDL_Renderer* renderer)
{
    //
    // renders a rectangle around the position
    // the position is the midpoint of the rectangle
    // not the top left corner
    //
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int hw = width/2;
    int hh = height/2;
    SDL_RenderDrawLine(renderer, position.get_x()-hw, position.get_y()-hh, position.get_x()+hw, position.get_y()-hh );
    SDL_RenderDrawLine(renderer, position.get_x()+hw, position.get_y()-hh, position.get_x()+hw, position.get_y()+hh );
    SDL_RenderDrawLine(renderer, position.get_x()+hw, position.get_y()+hh, position.get_x()-hw, position.get_y()+hh );
    SDL_RenderDrawLine(renderer, position.get_x()-hw, position.get_y()+hh, position.get_x()-hw, position.get_y()-hh );
}

int Rectangle::get_widht() { return width; }
int Rectangle::get_height() { return height; }
void Rectangle::set_width(int w) { width = w; }
void Rectangle::set_height(int h) { height = h; }
