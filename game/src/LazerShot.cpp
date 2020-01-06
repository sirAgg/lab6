#include "LazerShot.h"

#include "Model.h"
#include "Game.h"


//
// Create Model for LazerShot
// It's just a single line
//
glm::vec3 lazer_shot_model_points[] = 
{
    {0.0f,0.0f,0.0f},
    {0.0f,1.0f,0.0f}
};

Line lazer_shot_model_lines = 
{
    0,1
};

const Model LazerShot::lazer_shot_model = {
    (glm::vec3*)&lazer_shot_model_points,
    2,
    (Line*)&lazer_shot_model_lines,
    1
};

const float LAZER_SHOT_SIZE = 0.1f;

LazerShot::LazerShot(Point2D pos, ModelShape* shape, float speed, float stop_position):
    GameObject(pos, shape, LAZER_SHOT_SIZE), speed(speed), stop_position(stop_position)
{
    
}

bool LazerShot::update()
{
    position.set_y(position.get_y() + speed);
    if(position.get_y() < stop_position)
        return false;

    //
    // Asteroid Collision
    //
    for(auto asteroid: *Game::get_game()->get_asteroids())
    {
        if(is_colliding_with(asteroid))
        {
            asteroid->take_damage();
            return false; 
        } 
    }
    return true;
}
