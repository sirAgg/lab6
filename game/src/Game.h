#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

#include "SDL.h"
#include "glm/glm.hpp"

#include "Shape.h"
#include "SpaceShip.h"

const unsigned char ACTION_UP = 1;
const unsigned char ACTION_DOWN = 1 << 1;
const unsigned char ACTION_LEFT = 1 << 2;
const unsigned char ACTION_RIGHT = 1 << 3;

class Game
{
public:
    Game(int window_width, int window_height);
    virtual ~Game();

    void run();

    bool update();

private:
    int window_width, window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Caching of projection matrix
    glm::mat4 proj_mat;

    // projection view matrix
    glm::mat4 pv_mat;

    std::vector<Shape*> shapes;

    SpaceShip* space_ship;

    unsigned char input_map;
};

#endif // __GAME_H_
