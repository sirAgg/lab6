#include "Asteroid.h"

#include <stdio.h>

#include "glm/gtc/matrix_transform.hpp"

#include "Game.h"
#include "GameConstants.h"
#include "autogen/generated_models.h"

Asteroid::Asteroid( Point2D pos, glm::vec3 rotation_axis, float speed)
    :GameObject(pos, new ModelShape(Point2D(0,0), ASTEROID_COLOR,&GeneratedModels::asteroid_1_model), ASTEROID_SIZE), rotation_axis(rotation_axis), speed(speed)
{
    rotation = 0.0f;
    health = ASTEROID_HEALTH;
    color = ASTEROID_COLOR;
}

bool Asteroid::update()
{
    //
    // Check healt
    //
    if(health <= 0)
    {
        // asteroid is dead
        Game::get_game()->spawn_particles(position, rotation_axis, rotation);
        Game::get_game()->increase_score(ASTEROID_KILL_SCORE);
        return false;
    }

    // update rotation and position
    rotation = rotation + ASTEROID_ROTATION_SPEED;
    position.set_y(position.get_y() + speed );

    // The Asteroid is outside Game field
    if(position.get_y() > GAME_FIELD_NEAR_EDGE)
        return false;

    // fade in effect
    if(position.get_y() < ASTEROID_FADE_IN_AT)
    {
        float t = (position.get_y() - GAME_FIELD_FAR_EDGE)/(ASTEROID_FADE_IN_AT-GAME_FIELD_FAR_EDGE);
        Color c = color.scale(t);
        shape->set_color(c);
    }

    // fade out effect
    if(position.get_y() > ASTEROID_FADE_OUT_AT)
    {
        float t = (GAME_FIELD_NEAR_EDGE - position.get_y())/(GAME_FIELD_NEAR_EDGE-ASTEROID_FADE_OUT_AT);
        Color c = color.scale(t);
        shape->set_color(c);
    }

    return true;
}

void Asteroid::update_model_mat()
{
    //
    // Update model matrix for this Asteroids shape
    //
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, rotation, rotation_axis);
    shape->set_model_mat(m);
}

void Asteroid::take_damage()
{
    health--;

    // decrease color after each hit
    color = color.toInt() - 0x28282828;
    shape->set_color(color);
}
