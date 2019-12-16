#include <stdio.h>

#include <vector>
#include <cstdlib>
#include <time.h>
#include "SDL.h"

#include "Point2D.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

const int window_width  = 600;
const int window_height = 400;

Rectangle* create_random_rectange()
{
    return new Rectangle(
            Point2D((float)(rand()%window_width), (float)(rand()%window_height) ),
			Color(rand(), rand(), rand(), 255),
            rand()%window_width,
            rand()%window_height);
}
Triangle* create_random_triangle()
{
    return new Triangle(
            Point2D((float)(rand()%window_width), (float)(rand()%window_height) ),
			Color(rand(), rand(), rand(), 255), 
            rand()%window_width,
            rand()%window_height);
}
Circle* create_random_circle()
{
    return new Circle(
            Point2D((float)(rand()%window_width), (float)(rand()%window_height) ),
			Color(rand(), rand(), rand(), 255),
            rand()%window_height);
}

int main(int argc, char** argv)
{
    // initilize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
            "Hello there", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            window_width,window_height, 
            SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    srand(time(0));
    std::vector<Shape*> shapes;

    bool run = true;

    while (run)
    {
		int start_time = SDL_GetTicks();


        // event handeling
        while(SDL_PollEvent(&event))
        {
            switch (event.type) {
                // close window
                case SDL_QUIT:
                    run = false;
                    break;

                // handle Keyboard input
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_r:
                            shapes.push_back(create_random_rectange());
                            break;
                        case SDLK_t:
                            shapes.push_back(create_random_triangle());
                            break;
                        case SDLK_c:
                            shapes.push_back(create_random_circle());
                            break;
                        default:
                            break;
                    } break;
                default:
                    break;
            }
        }
        
        //printf("Shapes: %d\n", (int)rectangles.size() + (int)triangles.size() + (int)circles.size());

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (auto shape : shapes)
            shape->render(renderer);

        SDL_RenderPresent(renderer);
		

		if(start_time < 16)
			SDL_Delay(16-start_time);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
