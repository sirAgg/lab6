#include <stdio.h>

#include <vector>
#include <cstdlib>
#include <time.h>
#include "SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

glm::vec3 cube[] 
{
    {0.0f,0.0f,0.0f},
    {1.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,1.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,1.0f},
    
    {1.0f,0.0f,0.0f},
    {1.0f,1.0f,0.0f},
    {1.0f,0.0f,0.0f},
    {1.0f,0.0f,1.0f},
    
    {0.0f,1.0f,0.0f},
    {1.0f,1.0f,0.0f},
    {0.0f,1.0f,0.0f},
    {0.0f,1.0f,1.0f},
    
    {0.0f,0.0f,1.0f},
    {1.0f,0.0f,1.0f},
    {0.0f,0.0f,1.0f},
    {0.0f,1.0f,1.0f},
    
    {1.0f,1.0f,1.0f},
    {0.0f,1.0f,1.0f},
    {1.0f,1.0f,1.0f},
    {1.0f,0.0f,1.0f},
    {1.0f,1.0f,1.0f},
    {1.0f,1.0f,0.0f}
};

void print_two_vec3(glm::vec3& v1, glm::vec3& v2)
{
    printf("(%f,%f,%f) -> (%f,%f,%f)\n", 
            v1.x,v1.y,v1.z,
            v2.x,v2.y,v2.z);
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


    // create projection matrix
    glm::mat4 post_trans = glm::mat4(1.0f);
    //post_trans = glm::translate(post_trans, glm::vec3(0.0f, (float)window_height, 0.0f)); // for inverting Y
    post_trans = glm::scale(post_trans, glm::vec3((float)window_width/2.0f, (float)window_height/2.0f, 1.0f));
    post_trans = glm::translate(post_trans, glm::vec3(1.0f, 1.0f, 0.0f));


    glm::mat4 proj_mat = glm::perspective(glm::radians(45.0f), (float)window_width/(float)window_height, 0.1f, 100.0f);

    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, glm::vec3( 0.0f, 0.0f, 0.0f ));
    model_mat = glm::scale(model_mat, glm::vec3( 0.3f ) );
    //printf("[%f,%f,%f,%f]\n",proj_mat[0][0],proj_mat[0][1],proj_mat[0][2],proj_mat[0][3]);
    //printf("[%f,%f,%f,%f]\n",proj_mat[1][0],proj_mat[1][1],proj_mat[1][2],proj_mat[1][3]);
    //printf("[%f,%f,%f,%f]\n",proj_mat[2][0],proj_mat[2][1],proj_mat[2][2],proj_mat[2][3]);
    //printf("[%f,%f,%f,%f]\n",proj_mat[3][0],proj_mat[3][1],proj_mat[3][2],proj_mat[3][3]);

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto shape : shapes)
            shape->render(renderer);


        { // render wireframe cube

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            glm::vec4 pos1 = post_trans * proj_mat * glm::vec4( 0.0f,0.0f,1.0f,1.0f );
            glm::vec4 pos2 = post_trans * proj_mat * glm::vec4( 1.0f,1.0f,1.0f, 1.0f );
            SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
            SDL_Point p2 = {(int)pos2.x,(int)pos2.y};
            printf("(%f,%f) -> (%f,%f)\n", pos1.x, pos1.y, pos2.x, pos2.y );
            SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );

            //printf("-----\n");
            /*
            for (int i = 0; i < 24; i+=2)
            {
                glm::vec4 pos1 = post_trans * proj_mat * model_mat * glm::vec4( cube[i], 1.0f );
                glm::vec4 pos2 = post_trans * proj_mat * model_mat * glm::vec4( cube[i+1], 1.0f );
                SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
                SDL_Point p2 = {(int)pos2.x,(int)pos2.y};

                //print_two_vec3(cube[i], cube[i+1]);
                //printf("(%f,%f) -> (%f,%f)\n", pos1.x, pos1.y, pos2.x, pos2.y );

                SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
            }
            */
        }
		
        SDL_RenderPresent(renderer);

		if(start_time < 16)
			SDL_Delay(16-start_time);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
