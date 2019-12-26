#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 pos, ModelShape* shape)
    :GameObject(pos, shape)
{
    target_pos = pos;
}

void SpaceShip::update()
{
    glm::vec3 move_dir = target_pos - position;
    if ( glm::length(move_dir) > 0.001f)
    {
        position += move_dir * 0.0003f;
    }

    // printf("%f,%f,%f\n", position.x, position.y, position.z);
}

void SpaceShip::move_up()
{
    target_pos.y += TARGET_MOVE_SPEED;
}
void SpaceShip::move_down()
{
    target_pos.y -= TARGET_MOVE_SPEED;
}
void SpaceShip::move_left()
{
    target_pos.x -= TARGET_MOVE_SPEED;
}
void SpaceShip::move_right()
{
    target_pos.x += TARGET_MOVE_SPEED;
}
