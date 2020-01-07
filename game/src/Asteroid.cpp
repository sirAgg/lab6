#include "Asteroid.h"

#include <stdio.h>

#include "glm/gtc/matrix_transform.hpp"

#include "Game.h"
#include "autogen/generated_models.h"

const float ASTEROID_SIZE = 0.9f;;
const int ASTEROID_KILL_SCORE = 5;

Asteroid::Asteroid( Point2D pos, glm::vec3 rotation_axis, float speed, float rotation_speed, float stop_position, float fade_distance)
    :GameObject(pos, new ModelShape(Point2D(0,0),0xFFFFFFFF,&GeneratedModels::asteroid_1_model), ASTEROID_SIZE), rotation_axis(rotation_axis), speed(speed), rotation_speed(rotation_speed), stop_position(stop_position), fade_distance(fade_distance)
{
    rotation = 0.0f;
    start_position = position.get_y();
    health = 4;

    color = Color(0xFFFFFFFF);
}

bool Asteroid::update()
{
    if(health <= 0)
    {
        Game::get_game()->increase_score(ASTEROID_KILL_SCORE);
        Game::get_game()->spawn_particles(position);
        return false;
    }

    rotation = rotation + rotation_speed;
    position.set_y(position.get_y() + speed );

    if(position.get_y() > stop_position)
        return false;

    // fade in effect
    if(position.get_y() < start_position + fade_distance)
    {
        float t = (position.get_y() - start_position)/fade_distance;
        Color c = color.scale(t);
        shape->set_color(c);
    }

    // fade out effect
    if(position.get_y() > stop_position-fade_distance)
    {
        float t = (stop_position - position.get_y())/fade_distance;
        Color c = color.scale(t);
        shape->set_color(c);
    }
    return true;
}

void Asteroid::update_model_mat()
{
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, rotation, rotation_axis);
    shape->set_model_mat(m);
}

void Asteroid::take_damage()
{
    health--;
    color = color.scale(0.8);
    shape->set_color(color);
}
