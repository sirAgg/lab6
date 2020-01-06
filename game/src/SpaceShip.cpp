#include "SpaceShip.h"

#include <stdio.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"

const float MOVE_FACTOR = 0.1f;
const float TARGET_MOVE_SPEED = 0.15f;
const float BORDER_DISTANCE = 7.0f;
const float SPACE_SHIP_SIZE = 0.8f;
const int SHOOTING_COOLDOWN_MAX_TIME = 15;

SpaceShip::SpaceShip(Point2D pos, ModelShape* shape)
    :GameObject(pos, shape, SPACE_SHIP_SIZE)
{
    target_x = pos.get_x();
}

bool SpaceShip::update()
{
    float move_dist = target_x - position.get_x();
    if ( abs(move_dist) > 0.001f)
    {
        position.set_x(position.get_x() + move_dist * MOVE_FACTOR);
    }

    //
    // Asteroid collision
    //
    for(auto asteroid: *Game::get_game()->get_asteroids())
    {
        if(is_colliding_with(asteroid))
           printf("you dead\n"); 
    }
    
    return true;
}

void SpaceShip::update_model_mat()
{
    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));
    m = glm::rotate(m, 0.3f * (position.get_x() - target_x) , glm::vec3(0.0f,0.0f,1.0f));
    m = glm::rotate(m, 0.4f * (position.get_x() - target_x) , glm::vec3(0.0f,1.0f,0.0f));
    m = glm::scale(m, glm::vec3(1.0f,1.0f,-1.0f));
    shape->set_model_mat(m);
}

void SpaceShip::input_update(InputActions input)
{
    if(input & ACTION_LEFT)
    {
        target_x -= TARGET_MOVE_SPEED;

        if(target_x < -BORDER_DISTANCE)
            target_x = -BORDER_DISTANCE;
    }

    if(input & ACTION_RIGHT)
    {
        target_x += TARGET_MOVE_SPEED;
        if(target_x > BORDER_DISTANCE)
            target_x = BORDER_DISTANCE;
    }

    if(input & ACTION_UP && shooting_cooldown <= 0)
    {
        Game::get_game()->spawn_lazer_shot(position);
        shooting_cooldown = SHOOTING_COOLDOWN_MAX_TIME;
    }
    else if(shooting_cooldown > 0)
        shooting_cooldown--;
}
