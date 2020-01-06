#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

#include "SDL.h"
#include "glm/glm.hpp"

#include "Shape.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "LazerShot.h"
#include "InputActions.h"

const int ASTEROID_SPAWN_TIMER_START = 120;

class Game
{
public:
    Game(int window_width, int window_height);
    virtual ~Game();

    static Game* get_game();

    void run();

    void spawn_asteroid();
    void spawn_lazer_shot(Point2D pos);

    void increase_score(int increase);

    const std::vector<Asteroid*>* get_asteroids();

private:

    bool update();
    bool process_events();

    static Game* current_game;

    int window_width, window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Caching of projection matrix
    glm::mat4 proj_mat;
    glm::mat4 pv_mat;  // projection view matrix
    glm::vec3 camera_pos;

    // GameObjects
    SpaceShip* space_ship;
    std::vector<Asteroid*> asteroids;
    std::vector<LazerShot*> lazer_shots;

    float asteroid_speed = 0.2f;

    InputActions inputs;

    int asteroid_spawn_timer = 0;

    int score = 0;
};

#endif // __GAME_H_
