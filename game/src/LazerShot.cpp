#include "LazerShot.h"

#include "Game.h"
#include "GameConstants.h"

//
// Hardcode a Model for the LazerShot
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
const Model LazerShot::lazer_shot_model = 
{
    (glm::vec3*)&lazer_shot_model_points,
    2,
    (Line*)&lazer_shot_model_lines,
    1
};


LazerShot::LazerShot(Point2D pos, float speed)
    :GameObject(pos, new ModelShape(Point2D(),LAZER_SHOT_COLOR,&lazer_shot_model), LAZER_SHOT_SIZE), speed(speed)
{
    
}

bool LazerShot::update()
{
    // update position
    position.set_y(position.get_y() + speed);

    // if the shot is outside the game field
    if(position.get_y() < GAME_FIELD_FAR_EDGE)
        return false;

    // Asteroid Collision
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
