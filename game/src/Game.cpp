#include "Game.h"

#include <algorithm>

#include "glm/gtc/matrix_transform.hpp"

#include "Triangle.h"
#include "ModelShape.h"
#include "autogen/space_ship_model.h"
#include "autogen/asteroid_1_model.h"

Game::Game(int window_width, int window_height)
    :window_width(window_width), window_height(window_height)
{
    //
    // Initialize SDL
    //
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow(
                "Hello there",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                window_width,window_height,
                SDL_WINDOW_SHOWN
        );
        renderer = SDL_CreateRenderer(window, -1, 0);
    }

    //
    // Create projection and view matrices
    //
    camera_pos = glm::vec3(0.0f,3.0f,7.0f);
    {
        // matrix for mapping homogeneous coordinates to screen-coordinates
        glm::mat4 post_trans = glm::mat4(1.0f);
        post_trans = glm::scale(post_trans, glm::vec3((float)window_width/2.0f, -(float)window_height/2.0f, 1.0f));
        post_trans = glm::translate(post_trans, glm::vec3(1.0f, -1.0f, 0.0f));

        // create projection matrix
        proj_mat = glm::perspective(glm::radians(90.0f), (float)window_width/(float)window_height, 0.1f, 100.0f);

        // create view matrix
        glm::mat4 view_mat = glm::mat4(1.0f);
        view_mat = glm::scale(view_mat, glm::vec3(0.3f));
        view_mat = glm::translate(view_mat, -camera_pos);
        view_mat = glm::rotate(view_mat, glm::radians(90.0f + 20.0f), glm::vec3(1.0f,0.0f,0.0f));

        pv_mat = post_trans * proj_mat * view_mat;
    }

    // 
    // Spawn player
    //  

    ModelShape* space_ship_m = new ModelShape(Point2D(), 0xFFFF00FF, &space_ship_model, &pv_mat);
    space_ship = new SpaceShip(Point2D(0.0f,0.0f), space_ship_m);
    shapes.push_back(space_ship_m);

    spawn_asteroid();

    asteroid_spawn_timer = ASTEROID_SPAWN_TIMER_START;
}

Game::~Game()
{
    for(auto shape : shapes )
        delete shape;

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run()
{
    int start_time = SDL_GetTicks();

    while (update())
    {
        int delta_time = SDL_GetTicks()-start_time;
        if(delta_time < 16)
            SDL_Delay(16-delta_time);

        start_time = SDL_GetTicks();
    }
}

bool Game::update()
{
    // event handeling
    if(!process_events())
        return false;

    if(input_map & ACTION_LEFT) space_ship->move_left();
    if(input_map & ACTION_RIGHT) space_ship->move_right();

    space_ship->update();
    space_ship->update_model_mat();

    if(asteroid_spawn_timer <= 0)
    {
        spawn_asteroid();
        asteroid_spawn_timer = ASTEROID_SPAWN_TIMER_START;
    }
    else
        asteroid_spawn_timer--;

    for(auto it = asteroids.begin(); it != asteroids.end(); it++)
    {
        (*it)->update();
        if((*it)->get_position().get_y() > camera_pos.y - 1.0f)
        {
            delete (*it);
            asteroids.erase(it);
        }
        else
            (*it)->update_model_mat();
    }

    //
    // rendering
    //
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(auto it = shapes.begin(); it != shapes.end(); it++)
    {
        if((*it)->is_alive())
            (*it)->render(renderer);
        else
        {
            delete (*it);
            shapes.erase(it);
        }
    }

    // render orientation indicator
    /*
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        glm::vec4 pos1 = pv_mat * glm::vec4( 0.0f,0.0f,0.0f,1.0f );
        glm::vec4 pos2 = pv_mat * glm::vec4( 1.0f,0.0f,0.0f, 1.0f );
        pos1 /= pos1.w;
        pos2 /= pos2.w;
        SDL_Point p1 = {(int)pos1.x,(int)pos1.y};
        SDL_Point p2 = {(int)pos2.x,(int)pos2.y};
        SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        pos2 = pv_mat * glm::vec4( 0.0f,1.0f,0.0f, 1.0f );
        pos2 /= pos2.w;
        p2 = {(int)pos2.x,(int)pos2.y};
        SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        pos2 = pv_mat * glm::vec4( 0.0f,0.0f,-1.0f, 1.0f );
        pos2 /= pos2.w;
        p2 = {(int)pos2.x,(int)pos2.y};
        SDL_RenderDrawLine( renderer, p1.x, p1.y, p2.x, p2.y );
    }
    */

    SDL_RenderPresent(renderer);

    return true;
}

bool Game::process_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type) {
            // close window
            case SDL_QUIT:
                return false;
                break;

            // handle Keyboard input
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP: input_map |= ACTION_UP; break;
                    case SDLK_DOWN: input_map |= ACTION_DOWN; break;
                    case SDLK_LEFT: input_map |= ACTION_LEFT; break;
                    case SDLK_RIGHT: input_map |= ACTION_RIGHT; break;
                    default:
                        break;
                } break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP: input_map &= ~ACTION_UP; break;
                    case SDLK_DOWN: input_map &= ~ACTION_DOWN; break;
                    case SDLK_LEFT: input_map &= ~ACTION_LEFT; break;
                    case SDLK_RIGHT: input_map &= ~ACTION_RIGHT; break;
                    default:
                        break;
                } break;
            default:
                break;
        }
    }
    return true;
}

void Game::spawn_asteroid()
{
    ModelShape* asteroid_m = new ModelShape(Point2D(), 0xFFFFFFFF, &asteroid_1_model, &pv_mat);
    asteroids.push_back(new Asteroid(Point2D(0.0f, -100.0f), asteroid_m, glm::vec3(1.0f,1.0f,1.0f), 0.2, 0.1f));
    shapes.push_back(asteroid_m);
}
