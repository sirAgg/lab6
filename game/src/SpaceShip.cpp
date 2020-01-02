#include "SpaceShip.h"

#include "glm/gtc/matrix_transform.hpp"

const float BORDER_DISTANCE = 7.0f;

SpaceShip::SpaceShip(Point2D pos, ModelShape* shape)
    :GameObject(pos, shape)
{
    target_x = pos.get_x();
}

void SpaceShip::update()
{
    float move_dist = target_x - position.get_x();
    if ( abs(move_dist) > 0.001f)
    {
        position.set_x(position.get_x() + move_dist * MOVE_FACTOR);
    }

    // printf("%f,%f,%f\n", position.x, position.y, position.z);
}

void SpaceShip::update_model_mat()
{
    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));
    m = glm::rotate(m, 0.3f * (position.get_x() - target_x) , glm::vec3(0.0f,0.0f,1.0f));
    m = glm::rotate(m, 0.3f * (position.get_x() - target_x) , glm::vec3(0.0f,1.0f,0.0f));
    m = glm::scale(m, glm::vec3(1.0f,1.0f,-1.0f));
    shape->set_model_mat(m);
}

void SpaceShip::move_left()
{
    target_x -= TARGET_MOVE_SPEED;

    if(target_x < -BORDER_DISTANCE)
        target_x = -BORDER_DISTANCE;
}

void SpaceShip::move_right()
{
    target_x += TARGET_MOVE_SPEED;
    if(target_x > BORDER_DISTANCE)
        target_x = BORDER_DISTANCE;
}
