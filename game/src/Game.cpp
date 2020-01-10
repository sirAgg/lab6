#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "glm/gtc/matrix_transform.hpp"

#include "GameConstants.h"
#include "ModelShape.h"
#include "FilledRectangle.h"
#include "ParticleSystem.h"
#include "autogen/generated_models.h"

Game* Game::current_game;


Game* Game::get_game()
{
    return current_game;
}

Game::Game(int window_width, int window_height)
    :window_width(window_width), window_height(window_height)
{
    // set current pointer to current game instance
    current_game = this;

    //
    // Initialize SDL
    //
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow(
                "Asteroid Game",
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
    glm::vec3 camera_pos = glm::vec3(0.0f,3.0f,7.0f);
    {
        // matrix for mapping homogeneous coordinates to screen-coordinates
        glm::mat4 post_trans = glm::mat4(1.0f);
        post_trans = glm::scale(post_trans, glm::vec3((float)window_width/2.0f, -(float)window_height/2.0f, 1.0f));
        post_trans = glm::translate(post_trans, glm::vec3(1.0f, -1.0f, 0.0f));

        // create projection matrix
        glm::mat4 proj_mat = glm::perspective(glm::radians(90.0f), (float)window_width/(float)window_height, 0.1f, 100.0f);

        // create view matrix
        glm::mat4 view_mat = glm::mat4(1.0f);
        view_mat = glm::scale(view_mat, glm::vec3(0.3f));
        view_mat = glm::translate(view_mat, -camera_pos);
        view_mat = glm::rotate(view_mat, glm::radians(90.0f + 20.0f), glm::vec3(1.0f,0.0f,0.0f));

        pv_mat = post_trans * proj_mat * view_mat;
    }

    //
    // initalize some fields
    //
    {
        game_over = false;
        asteroid_spawn_time = ASTEROID_SPAWN_TIMER_START;
        asteroid_spawn_timer = 0;
        asteroid_speed = ASTEROID_START_SPEED;
        srand(time(0));
        space_ship = new SpaceShip(Point2D(0.0f,0.0f), MAX_LIVES);

        // initialize lives counter 
        for(int i = 0; i < MAX_LIVES; i++)
            lives_counter_ui.push_back(new FilledRectangle(Point2D(15+30*i, 15),0xAA0000FF, 20,20));
    }
}

Game::~Game()
{
    // free everything
    delete space_ship; 
    for(auto asteroid : asteroids )
        delete asteroid;

    for(auto lazer: lazer_shots)
        delete lazer;

    for(auto particle: particles)
        delete particle;

    for(auto shape: lives_counter_ui)
        delete shape;

    // quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run()
{
    int start_time = SDL_GetTicks();

    while (update())
    {
        // Fix update rate at 60
        int delta_time = SDL_GetTicks()-start_time;
        if(delta_time < 16)
            SDL_Delay(16-delta_time);

        start_time = SDL_GetTicks();
    }
}

bool Game::update()
{
    //
    // event handeling
    //
    if(!process_events())
        return false;

    //
    // Spawn Asteroid Logic
    //
    {
        if(asteroid_spawn_timer <= 0)
        {
            spawn_asteroid();
            asteroid_spawn_timer = asteroid_spawn_time;
            if(asteroid_spawn_time > 20)
                asteroid_spawn_time--;
            else
                asteroid_speed += 0.01f;
        }
        else
            asteroid_spawn_timer--;
    }

    //
    // Update All GameObjects
    //
    {
        if (!game_over)
            if (!space_ship->update())
            {
                game_over = true;
                printf("You reached a score of: %d\n", score);
            }

        update_game_objects((std::vector<GameObject*>*)&asteroids);
        update_game_objects((std::vector<GameObject*>*)&lazer_shots);
        update_game_objects((std::vector<GameObject*>*)&particles);
    }

    //
    // Rendering
    //
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for(auto particle: particles)
            particle->render(renderer);
        for(auto lazer: lazer_shots)
            lazer->render(renderer);
        for(auto it = asteroids.rbegin(); it != asteroids.rend(); ++it)
            (*it)->render(renderer);

        space_ship->render(renderer);

        render_ui();

        SDL_RenderPresent(renderer);
    }

    return true;
}

void Game::update_game_objects(std::vector<GameObject*>* objects)
{
    for(auto it = objects->begin(); it != objects->end();)
    {
        // if an objects update function returns false it's dead 
        // and needs to be removed
        if(!(*it)->update())
        {
            delete (*it);
            it = objects->erase(it);
			continue;
        }
		it++;
    }
}

bool Game::process_events()
{
    //
    // Loop throu every avaible event
    // Returning false means the game should exit
    //
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
                    case SDLK_UP: inputs |= ACTION_SHOOT; break;
                    case SDLK_LEFT: inputs |= ACTION_LEFT; break;
                    case SDLK_RIGHT: inputs |= ACTION_RIGHT; break;
                    default:
                        break;
                } break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP: inputs &= ~ACTION_SHOOT; break;
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

void Game::render_ui()
{ 
    //
    // Render the ui
    // Currently the only ui element is the life counter in the top left corner
    //
    int i = 1;
    if( space_ship->get_lives() < lives_counter_ui.size() && lives_counter_ui.size() >= 0 )
        lives_counter_ui.pop_back();
    for(auto s: lives_counter_ui)
    {
        s->render(renderer);    
        i++;
    }
}

void Game::spawn_asteroid()
{
    //
    // Spawn Asteroid with:
    //   random X-pos
    //   random rotation-axis
    //   At the far end of the game field
    //
    Point2D pos;
    pos.set_x((float)rand()/(float)RAND_MAX*GAME_FIELD_WIDTH*2.0f - GAME_FIELD_WIDTH);
    pos.set_y(GAME_FIELD_FAR_EDGE);
    glm::vec3 rotation_axis = glm::vec3();
	rotation_axis.x = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;
	rotation_axis.y = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;
	rotation_axis.z = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;

    asteroids.push_back(new Asteroid(pos, rotation_axis, asteroid_speed));
}

void Game::spawn_lazer_shot(Point2D pos)
{
    //
    // Creates new LazerShot
    //
    lazer_shots.push_back(new LazerShot(pos, LAZER_SHOT_SPEED));
}

void Game::spawn_particles(Point2D pos, glm::vec3 rotation_axis, float rotation)
{
    //
    // Spawn a particle System
    //
    particles.push_back(new ParticleSystem(
                pos,
                0xFFFFFFFF,
                &GeneratedModels::asteroid_1_model,
                rotation_axis,
                rotation,
                PARTICLE_SYSTEM_LIFE_LENGHT,
                PARTICLE_SYSTEM_FADE_OUT_START_TIME));
}

void Game::increase_score(int increase)
{
    score += increase;
}

const std::vector<Asteroid*>* Game::get_asteroids()
{
    return &asteroids;
}

const InputActions Game::get_inputs() const
{
    return inputs;
}

const glm::mat4* Game::get_pv_mat() const
{
    return &pv_mat;
}
