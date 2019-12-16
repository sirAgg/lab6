#include "Circle.h"

#include <stdio.h>
#include <math.h>

const int CIRCLE_RESOLUTION = 32;

Circle::Circle(Point2D pos, Color color, int radius)
    : Shape(pos, color), radius(radius)
{}

void Circle::render(SDL_Renderer* renderer)
{
    printf("CIRCLE:\n\tpos: %s\n\tcolor: %08X\n\tradius: %d\n",
         position.to_string().c_str(), color.toInt(), radius);
    
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a );

    float angle1 = 0.0f;
    float angle2 = 0.0f;
    for (int i = 0; i < CIRCLE_RESOLUTION; ++i) {
        angle1 += M_PI*2.0f/(float)CIRCLE_RESOLUTION;
        SDL_RenderDrawLine(renderer, position.get_x()+radius*cos(angle2), position.get_y()+radius*sin(angle2), position.get_x()+radius*cos(angle1), position.get_y()+radius*sin(angle1));
        angle2 = angle1;
    }
}

int Circle::get_radius() { return radius; }
void Circle::set_radius(int r) { radius = r; }
