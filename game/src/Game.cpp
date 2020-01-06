#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "glm/gtc/matrix_transform.hpp"

#include "ModelShape.h"
#include "autogen/space_ship_model.h"
#include "autogen/asteroid_1_model.h"

Game* Game::current_game;

Game* Game::get_game()
{
    return current_game;
}

Game::Game(int window_width, int window_height)
    :window_width(window_width), window_height(window_height)
{
    current_game = this;
    srand(time(0));
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

    spawn_asteroid();

    asteroid_spawn_timer = ASTEROID_SPAWN_TIMER_START;
}

Game::~Game()
{
    for(auto asteroid : asteroids )
        delete asteroid;

    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("You reached a score of: %d\n", score);
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

    space_ship->input_update(inputs);


    //
    // Spawn Asteroid
    //
    if(asteroid_spawn_timer <= 0)
    {
        spawn_asteroid();
        asteroid_spawn_timer = ASTEROID_SPAWN_TIMER_START;
    }
    else
        asteroid_spawn_timer--;


    //
    // Update All GameObjects
    //
    space_ship->update();
    space_ship->update_model_mat();

    for(auto it = asteroids.begin(); it != asteroids.end(); it++)
    {
        if((*it)->update())
        {
            (*it)->update_model_mat();
        }
        else
        {
            delete (*it);
            it = asteroids.erase(it);
            it--;
        }
    }
    
    for(auto it = lazer_shots.begin(); it != lazer_shots.end(); it++)
    {
        if((*it)->update())
        {
            (*it)->update_model_mat();
        }
        else
        {
            delete (*it);
            it = lazer_shots.erase(it);
            it--;
        }
    }

    //
    // Rendering
    //
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(auto lazer: lazer_shots)
        lazer->render(renderer);
    for(auto asteroid: asteroids)
        asteroid->render(renderer);

    space_ship->render(renderer);

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
                    case SDLK_UP: inputs |= ACTION_UP; break;
                    case SDLK_DOWN: inputs |= ACTION_DOWN; break;
                    case SDLK_LEFT: inputs |= ACTION_LEFT; break;
                    case SDLK_RIGHT: inputs |= ACTION_RIGHT; break;
                    default:
                        break;
                } break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP: inputs &= ~ACTION_UP; break;
                    case SDLK_DOWN: inputs &= ~ACTION_DOWN; break;
                    case SDLK_LEFT: inputs &= ~ACTION_LEFT; break;
                    case SDLK_RIGHT: inputs &= ~ACTION_RIGHT; break;
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
    Point2D pos;
    pos.set_x((float)rand()/(float)RAND_MAX*GAME_FIELD_WIDTH*2.0f - GAME_FIELD_WIDTH);
    pos.set_y(-100.0f);

    ModelShape* asteroid_m = new ModelShape(Point2D(), 0xFFFFFFFF, &asteroid_1_model, &pv_mat);
    asteroids.push_back(new Asteroid(pos, asteroid_m, glm::vec3(1.0f,1.0f,1.0f), asteroid_speed, 0.1f, camera_pos.y+2.0f, 7.0f));

    asteroid_speed += 0.01f;
}

void Game::spawn_lazer_shot(Point2D pos)
{
    ModelShape* lazer_shot_m = new ModelShape(Point2D(), 0xFF5555FF, &LazerShot::lazer_shot_model, &pv_mat);
    lazer_shots.push_back(new LazerShot(pos, lazer_shot_m, -0.4, -100.0f));
}

const std::vector<Asteroid*>* Game::get_asteroids()
{
    return &asteroids;
}

void Game::increase_score(int increase)
{
    score += increase;
}
