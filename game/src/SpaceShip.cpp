#include "SpaceShip.h"

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"
#include "autogen/generated_models.h"
#include "GameConstants.h"


SpaceShip::SpaceShip(Point2D pos, int lives)
    :GameObject(pos, new ModelShape(Point2D(0,0),0xFFFF00FF,&GeneratedModels::space_ship_model), SPACESHIP_SIZE), lives(lives)
{
	color = 0xFFFF00FF;
    target_x = pos.get_x();
}

bool SpaceShip::update()
{
    // 
    // React to inputs
    //
    InputActions input = Game::get_game()->get_inputs();
    if(input & ACTION_LEFT)
    {
        target_x -= SPACESHIP_MOVE_SPEED;

        if(target_x < -GAME_FIELD_WIDTH)
            target_x = -GAME_FIELD_WIDTH;
    }

    if(input & ACTION_RIGHT)
    {
        target_x += SPACESHIP_MOVE_SPEED;
        if(target_x > GAME_FIELD_WIDTH)
            target_x = GAME_FIELD_WIDTH;
    }

    if((input & ACTION_SHOOT) && shooting_cooldown <= 0)
    {
        // spawn LazerShot infront of spaceship
        Game::get_game()->spawn_lazer_shot(Point2D(position.get_x(), position.get_y()-1.7f));
        shooting_cooldown = SPACESHIP_SHOOTING_COOLDOWN_TIME_MAX;
    }
    else if(shooting_cooldown > 0)
        shooting_cooldown--;

    //
    // Move to target x
    //
    float move_dist = target_x - position.get_x();
    if ( abs(move_dist) > 0.001f)
    {
        position.set_x(position.get_x() + move_dist * SPACESHIP_RESPONSIVENESS);
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
                // spaceship is hit
                invincibility_time = SPACESHIP_INVINCIBILITY_TIME_MAX;
                lives--;
				if (lives <= 0)
				{
                    // Spaceship is dead
					Game::get_game()->spawn_particles(position, glm::vec3(1.0f, 0.0f, 0.0f), M_PI_2);
					shape->set_color(0);
					return false;
				}
            }
        }
    }
	else
	{
        // spaceship is invincible
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
    //
    // Update model matrix for spaceship shape
    //
    
    // position
    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(position.get_x(), position.get_y(), 0.0f));

    // rotation
    m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f)); // rotate to correct orientation
    m = glm::rotate(m, 0.3f * (position.get_x() - target_x) , glm::vec3(0.0f,0.0f,1.0f));
    m = glm::rotate(m, 0.4f * (position.get_x() - target_x) , glm::vec3(0.0f,1.0f,0.0f));

    // scale
    m = glm::scale(m, glm::vec3(1.0f,1.0f,-1.0f));

    shape->set_model_mat(m);
}

int SpaceShip::get_lives()
{
    return lives;
}
