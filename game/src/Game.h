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
    void spawn_particles(Point2D pos, glm::vec3 rotation_axis, float rotation);

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
    int asteroid_spawn_time = 0;
    int score = 0;
	bool game_over;

    std::vector<Shape*> lives_counter_ui;
};

#endif // __GAME_H_
