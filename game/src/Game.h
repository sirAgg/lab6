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
const float GAME_FIELD_WIDTH = 7.0f;
const int MAX_LIVES = 5;

class Game
{
public:
    Game(int window_width, int window_height);
    virtual ~Game();

    static Game* get_game();

    void run();

    void spawn(GameObject* object);
    void spawn_asteroid();
    void spawn_lazer_shot(Point2D pos);
    void spawn_particles(Point2D pos);

    void increase_score(int increase);

    const std::vector<Asteroid*>* get_asteroids();
    const InputActions get_inputs() const; 
    const glm::mat4* get_pv_mat() const;

private:

    bool update();
    void update_game_objects(std::vector<GameObject*>* objects);
    bool process_events();
    void render_ui();

    static Game* current_game;

    int window_width, window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    glm::mat4 pv_mat;  // projection view matrix
    glm::vec3 camera_pos;

    // GameObjects
    SpaceShip* space_ship;
    std::vector<Asteroid*> asteroids;
    std::vector<LazerShot*> lazer_shots;
    std::vector<GameObject*> other_game_objects;
    
    InputActions inputs = 0;

    float asteroid_speed = 0.2f;
    int asteroid_spawn_timer = 0;
    int asteroid_spawn_delay = ASTEROID_SPAWN_TIMER_START;
    int score = 0;

    int lives;
    std::vector<Shape*> lives_counter_ui;
};

#endif // __GAME_H_
