#include "SpaceShip.h"

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"
#include "autogen/generated_models.h"

const float MOVE_FACTOR = 0.1f;
const float TARGET_MOVE_SPEED = 0.15f;
const float SPACE_SHIP_SIZE = 0.8f;
const int SHOOTING_COOLDOWN_MAX_TIME = 15;
const int INVINCIBILITY_TIME_MAX = 90;

SpaceShip::SpaceShip(Point2D pos, int lives)
    :GameObject(pos, new ModelShape(Point2D(0,0),0xFFFF00FF,&GeneratedModels::space_ship_model), SPACE_SHIP_SIZE), lives(lives)
{
	color = 0xFFFF00FF;
    target_x = pos.get_x();
}

bool SpaceShip::update()
{
    InputActions input = Game::get_game()->get_inputs();
    if(input & ACTION_LEFT)
    {
        target_x -= TARGET_MOVE_SPEED;

        if(target_x < -GAME_FIELD_WIDTH)
            target_x = -GAME_FIELD_WIDTH;
    }

    if(input & ACTION_RIGHT)
    {
        target_x += TARGET_MOVE_SPEED;
        if(target_x > GAME_FIELD_WIDTH)
            target_x = GAME_FIELD_WIDTH;
    }

    if(input & ACTION_UP && shooting_cooldown <= 0)
    {
        Game::get_game()->spawn_lazer_shot(Point2D(position.get_x(), position.get_y()-1.7));
        shooting_cooldown = SHOOTING_COOLDOWN_MAX_TIME;
    }
    else if(shooting_cooldown > 0)
        shooting_cooldown--;


    float move_dist = target_x - position.get_x();
    if ( abs(move_dist) > 0.001f)
    {
        position.set_x(position.get_x() + move_dist * MOVE_FACTOR);
    }

    //
    // Asteroid collision
    //
   
    if( invincibility_time <= 0)
    {
        for(auto asteroid: *Game::get_game()->get_asteroids())
        {
            if(is_colliding_with(asteroid))
            {
                invincibility_time = INVINCIBILITY_TIME_MAX;
                lives--;
				if (lives <= 0)
				{
					Game::get_game()->spawn_particles(position, glm::vec3(1.0f, 0.0f, 0.0f), M_PI_2);
					shape->set_color(0);
					return false;
				}
            }
        }
    }
	else
	{
		if (invincibility_time & 16)
			shape->set_color(0);
		else
			shape->set_color(color);
        invincibility_time--;
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

int SpaceShip::get_lives()
{
    return lives;
}
