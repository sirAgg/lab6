#include "Asteroid.h"

#include <stdio.h>

#include "glm/gtc/matrix_transform.hpp"

const float ASTEROID_SPEED = 0.2f;

Asteroid::Asteroid( Point2D pos, ModelShape* shape, glm::vec3 rotation_axis, float speed, float rotation_speed)
    :GameObject(pos, shape), rotation_axis(rotation_axis), speed(speed), rotation_speed(rotation_speed)
{
    rotation = 0.0f;
}

Asteroid::~Asteroid()
{
    shape->destroy();
}

void Asteroid::update()
{
    rotation = rotation + rotation_speed;
    position.set_y(position.get_y() + speed );
    // printf("z: %f\n", position.z);

    // fade out effect
    if(position.get_y() > 0.0f)
    {
        float t = (9.0f - position.get_y())/9.0f * 255.0f;
        Color c((int)t, (int)t, (int)t, (int)t);
        shape->set_color(c);
    }
}

void Asteroid::update_model_mat()
{
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, rotation, rotation_axis);
    shape->set_model_mat(m);
}
