#include "SevenSegShape.h"

struct Point{int x,y;};
struct Line{Point a,b;};

Point points[] =
{
    {0,0},
    {1,0},
    {0,1},
    {1,1},
    {0,2},
    {1,2}
};

const unsigned char number_0 = 0b01111111;
const unsigned char number_1 = 0b00100100;
const unsigned char number_2 = 0b01011101;
const unsigned char number_3 = 0b01101101;
const unsigned char number_4 = 0b00101110;
const unsigned char number_5 = 0b01101011;
const unsigned char number_6 = 0b01111101;
const unsigned char number_7 = 0b00100101;
const unsigned char number_8 = 0b01111111;
const unsigned char number_9 = 0b00101111;

NumberShape::NumberShape(Point2D pos, Color color, unsigned char lines, float scale)
    :Shape(pos, color), lines(lines), scale(scale)
{
}

NumberShape::NumberShape(Point2D pos, Color color, int number, float scale)
    :Shape(pos, color), number(number), scale(scale)
{
	switch(number % 10)
    {
        case 0: lines = number_0; break;
        case 1: lines = number_1; break;
        case 2: lines = number_2; break;
        case 3: lines = number_3; break;
        case 4: lines = number_4; break;
        case 5: lines = number_5; break;
        case 6: lines = number_6; break;
        case 7: lines = number_7; break;
        case 8: lines = number_8; break;
        case 9: lines = number_9; break;
    }
}

void NumberShape::render(SDL_Renderer *renderer)
{


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int i = 0;
    while (lines[i].a != lines[i].b)
    {
        SDL_RenderDrawLine(renderer,
                             position.get_x() + points[lines[i].a].x * scale,
                             position.get_y() + points[lines[i].a].y * scale,
                             position.get_x() + points[lines[i].b].x * scale,
                             position.get_y() + points[lines[i].b].y * scale);
        i++;
    }
}

void NumberShape::set_number(int n)
{
    number = n;
}

void NumberShape::set_scale(float s)
{
    scale = s;
}

int NumberShape::get_number()
{
    return number;
}
