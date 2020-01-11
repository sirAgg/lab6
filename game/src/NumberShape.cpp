#include "NumberShape.h"

struct Line{unsigned char a,b;};
struct Point{int x,y;};

Point points[] =
{
    {0,0},
    {1,0},
    {0,1},
    {1,1},
    {0,2},
    {1,2}
};

Line line_data_0[] =
{
    {0,1},
    {1,3},
    {3,5},
    {5,4},
    {4,2},
    {2,0},
    {0,0},
};
Line line_data_1[] =
{
    {1,3},
    {3,5},
    {0,0},
};
Line line_data_2[] =
{
    {0,1},
    {1,3},
    {2,3},
    {5,4},
    {4,2},
    {0,0},
};
Line line_data_3[] =
{
    {0,1},
    {1,3},
    {3,5},
    {5,4},
    {2,3},
    {0,0},
};
Line line_data_4[] =
{
    {1,3},
    {3,5},
    {2,0},
    {2,3},
    {0,0},
};
Line line_data_5[] =
{
    {0,1},
    {3,5},
    {5,4},
    {2,0},
    {2,3},
    {0,0},
};
Line line_data_6[] =
{
    {0,1},
    {3,5},
    {5,4},
    {4,2},
    {2,0},
    {2,3},
    {0,0},
};
Line line_data_7[] =
{
    {0,1},
    {1,3},
    {3,5},
    {0,0},
};
Line line_data_8[] =
{
    {0,1},
    {1,3},
    {3,5},
    {5,4},
    {4,2},
    {2,0},
    {2,3},
    {0,0},
};
Line line_data_9[] =
{
    {0,1},
    {1,3},
    {3,5},
    {2,0},
    {2,3},
    {0,0},
};



NumberShape::NumberShape(Point2D pos, Color color, int number, float scale)
    :Shape(pos, color), number(number), scale(scale)
{
}

void NumberShape::render(SDL_Renderer *renderer)
{
    Line* lines;

    switch(number % 10)
    {
        case 0: lines = line_data_0; break;
        case 1: lines = line_data_1; break;
        case 2: lines = line_data_2; break;
        case 3: lines = line_data_3; break;
        case 4: lines = line_data_4; break;
        case 5: lines = line_data_5; break;
        case 6: lines = line_data_6; break;
        case 7: lines = line_data_7; break;
        case 8: lines = line_data_8; break;
        case 9: lines = line_data_9; break;
    }

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
