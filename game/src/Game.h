#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

#include "SDL.h"
#include "glm/glm.hpp"

#include "Shape.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "InputActions.h"

const int ASTEROID_SPAWN_TIMER_START = 120;

class Game
{
public:
    Game(int window_width, int window_height);
    virtual ~Game();

    void run();

    bool update();
    bool process_events();

    void spawn_asteroid();

private:
    int window_width, window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Caching of projection matrix
    glm::mat4 proj_mat;
    glm::mat4 pv_mat;  // projection view matrix
    glm::vec3 camera_pos;

    std::vector<Shape*> shapes;

    // GameObjects
    SpaceShip* space_ship;
    std::vector<Asteroid*> asteroids;

    InputActions input_map;

    int asteroid_spawn_timer = 0;
};

#endif // __GAME_H_
