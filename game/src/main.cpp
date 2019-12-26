#include <stdio.h>

#include <vector>
#include <time.h>
#include "SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Point2D.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "ModelShape.h"

#include "Game.h"

const int window_width  = 1000;
const int window_height = 800;


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

void render_model( SDL_Renderer* renderer, Model& model, glm::mat4& post_trans, glm::mat4& proj_mat, glm::mat4& view_mat, glm::mat4& model_mat)
{
    SDL_Point* points = new SDL_Point[model.n_points];

    glm::mat4 pv_mat = post_trans * proj_mat * view_mat;
    pv_mat *= model_mat;
    for (int i = 0; i < model.n_points; i++)
    {
        glm::vec4 pos = pv_mat * glm::vec4( model.points[i], 1.0f );

        pos /= pos.w;

        points[i] = {(int)pos.x,(int)pos.y};
    }

    for(int i = 0; i < model.n_lines; i++)
    {
        SDL_Point& p1 = points[model.lines[i].a];
        SDL_Point& p2 = points[model.lines[i].b];
        SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
    }
}

void print_two_vec3(glm::vec3& v1, glm::vec3& v2)
{
    printf("(%f,%f,%f) -> (%f,%f,%f)\n", 
            v1.x,v1.y,v1.z,
            v2.x,v2.y,v2.z);
}

int main(int argc, char** argv)
{
    Game game(1000,800);
    game.run();
}
    /*
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

    bool run = true;
    float rotation = 0;


    // matrix for mapping homogeneous coordinates to screen-coordinates
    glm::mat4 post_trans = glm::mat4(1.0f);
    post_trans = glm::scale(post_trans, glm::vec3((float)window_width/2.0f, -(float)window_height/2.0f, 1.0f));
    post_trans = glm::translate(post_trans, glm::vec3(1.0f, -1.0f, 0.0f));

    // create projection matrix
    glm::mat4 proj_mat = glm::perspective(glm::radians(90.0f), (float)window_width/(float)window_height, 0.1f, 100.0f);

    // create view matrix
    glm::mat4 view_mat = glm::mat4(1.0f);
    view_mat = glm::translate(view_mat, glm::vec3(0.0f,0.0f,2.0f));
    view_mat = glm::scale(view_mat, glm::vec3(0.3f));

    glm::mat4 pv_mat = post_trans * proj_mat * view_mat;

    ModelShape space_ship(Point2D(), Color(0xFFFFFFFF), &space_ship_model, &pv_mat);

    // main game loop
    while (run)
    {

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
                        default:
                            break;
                    } break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        space_ship.render(renderer);

        { // render wireframe cube
            glm::mat4 model_mat = glm::mat4(1.0f);
            model_mat = glm::translate(model_mat, glm::vec3( 0.0f, 0.0f, 2.0f ));
            model_mat = glm::rotate(model_mat, rotation, glm::vec3(1.0f, 0.5f, 0.7f));
            model_mat = glm::scale(model_mat, glm::vec3( 0.3f ) );
            rotation += 0.0001f;

            // printf("-----\n");
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // for (int i = 0; i < 24; i+=2)
            // {
            //     glm::vec4 pos1 = proj_mat * view_mat * model_mat * glm::vec4( cube[i], 1.0f );
            //     glm::vec4 pos2 = proj_mat * view_mat * model_mat * glm::vec4( cube[i+1], 1.0f );

            //     pos1 /= pos1.w;
            //     pos2 /= pos2.w;

            //     pos1 = post_trans * pos1;
            //     pos2 = post_trans * pos2;
            //     SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
            //     SDL_Point p2 = {(int)pos2.x,(int)pos2.y};

            //     SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
            // }

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            glm::vec4 pos1 = view_mat * glm::vec4( 0.0f,0.0f,0.0f,1.0f );
            glm::vec4 pos2 = view_mat * glm::vec4( 1.0f,0.0f,0.0f, 1.0f );
            pos1 = proj_mat * pos1;
            pos2 = proj_mat * pos2;
            pos1.w = 1.0f;
            pos2.w = 1.0f;

            pos1 = post_trans * pos1;
            pos2 = post_trans * pos2;
            SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
            SDL_Point p2 = {(int)pos2.x,(int)pos2.y};
            //printf("(%d,%d) -> (%d,%d)\n", p1.x, p1.y, p2.x, p2.y );
            SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                glm::vec4 pos1 = proj_mat * view_mat * glm::vec4( 0.0f,0.0f,0.0f,1.0f );
                glm::vec4 pos2 = proj_mat * view_mat * glm::vec4( 0.0f,1.0f,0.0f, 1.0f );
                pos1.w = 1.0f;
                pos2.w = 1.0f;
                pos1 = post_trans * pos1;
                pos2 = post_trans * pos2;
                SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
                SDL_Point p2 = {(int)pos2.x,(int)pos2.y};
                //printf("(%d,%d) -> (%d,%d)\n", p1.x, p1.y, p2.x, p2.y );
                SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                pos1 = proj_mat * view_mat * glm::vec4( 0.0f,0.0f,0.0f,1.0f );
                pos2 = proj_mat * view_mat * glm::vec4( 0.0f,0.0f,1.0f, 1.0f );
                pos1.w = 1.0f;
                pos2.w = 1.0f;
                pos1 = post_trans * pos1;
                pos2 = post_trans * pos2;
                p1 = {(int)pos1.x,(int)pos1.y};
                p2 = {(int)pos2.x,(int)pos2.y};
                //printf("(%d,%d) -> (%d,%d)\n", p1.x, p1.y, p2.x, p2.y );
                SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
            }

        }
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\033[0m");
    return 0;
}
*/
