#ifndef __GAME_H_
#define __GAME_H_

#include <vector>

#include "SDL.h"
#include "glm/glm.hpp"

#include "Shape.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "LazerShot.h"
#include "ParticleSystem.h"
#include "InputActions.h"

class Game
{
public:
    Game(int window_width, int window_height);
    virtual ~Game();

    static Game* get_game();

    void run();

    void spawn_asteroid();
    void spawn_lazer_shot(Point2D pos);
    void spawn_particles(Point2D pos, glm::vec3 rotation_axis, float rotation);

    void increase_score(int increase);

    // getters
    const std::vector<Asteroid*>* get_asteroids();
    const InputActions get_inputs() const; 
    const glm::mat4* get_pv_mat() const;

private:
    // functions only used by the game object itself
    bool update();
    void update_game_objects(std::vector<GameObject*>* objects);
    bool process_events();
    void render_ui();

    // reference to the current game so that 
    // other parts of the game can have access to the game object
    static Game* current_game;

    // SDL related data
    int window_width, window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    // projection view matrix
    glm::mat4 pv_mat;

    // GameObjects
    //
    // I separated all types of gameobjects 
    // so I can control n which order they are rendered
    //
    SpaceShip* space_ship;
    std::vector<Asteroid*> asteroids;
    std::vector<LazerShot*> lazer_shots;
    std::vector<ParticleSystem*> particles;

    // state of keyboard keys used in the game
    InputActions inputs = 0;

    // variables for spawning asteroids
    float asteroid_speed;
    int asteroid_spawn_timer;
    int asteroid_spawn_time;

    int score = 0;
	bool game_over;

    // shapes for displaying lifes
    std::vector<Shape*> lives_counter_ui;
};

#endif // __GAME_H_
