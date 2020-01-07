#include "FilledRectangle.h"

FilledRectangle::FilledRectangle(Point2D pos, Color color, int width, int height)
    :Rectangle(pos, color, width, height)
{}

void FilledRectangle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int hw = width/2;
    int hh = height/2;
    SDL_Rect rect{ (int)position.get_x() - hw, (int)position.get_y()-hh, width, height};
    SDL_RenderFillRect( renderer, &rect );
}
