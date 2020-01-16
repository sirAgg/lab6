#include "SevenSegShape.h"

struct Point{int x,y;};
struct Line{Point a,b;};

Line line_segments[] = 
{
{{4,0},{16,0}},
{{0,4},{0,16}},
{{20,4},{20,16}},
{{4,20},{16,20}},
{{0,24},{0,36}},
{{20,24},{20,36}},
{{4,40},{16,40}}
};
    
const unsigned char number_0 = 0b01110111;
const unsigned char number_1 = 0b00100100;
const unsigned char number_2 = 0b01011101;
const unsigned char number_3 = 0b01101101;
const unsigned char number_4 = 0b00101110;
const unsigned char number_5 = 0b01101011;
const unsigned char number_6 = 0b01111011;
const unsigned char number_7 = 0b00100101;
const unsigned char number_8 = 0b01111111;
const unsigned char number_9 = 0b00101111;

SevenSegShape::SevenSegShape(Point2D pos, Color color, unsigned char lines, float scale)
    :Shape(pos, color), lines(lines), scale(scale)
{
}

SevenSegShape::SevenSegShape(Point2D pos, Color color, int number, float scale)
    :Shape(pos, color), scale(scale)
{
    set_number(number);
}

void SevenSegShape::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    unsigned char mask = 1;

    for(int i = 0; i < 7; i++)
    {
        if(lines & mask)
        {
            SDL_RenderDrawLine(renderer,
                                position.get_x() + line_segments[i].a.x * scale,
                                position.get_y() + line_segments[i].a.y * scale,
                                position.get_x() + line_segments[i].b.x * scale,
                                position.get_y() + line_segments[i].b.y * scale);
        }
        mask <<= 1;
    }
}

void SevenSegShape::set_number(int n)
{
	switch(n % 10)
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

void SevenSegShape::set_scale(float s)
{
    scale = s;
}

void SevenSegShape::set_lines(unsigned char l)
{
    lines = l;
}
