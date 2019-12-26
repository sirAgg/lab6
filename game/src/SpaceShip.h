#ifndef __SPACESHIP_H_
#define __SPACESHIP_H_

#include "GameObject.h"
#include "ModelShape.h"

const float MOVE_SPEED = 0.00001f;
const float TARGET_MOVE_SPEED = 0.0005f;

class SpaceShip : public GameObject
{
public:
    SpaceShip(glm::vec3 pos, ModelShape* shape);

    void update();

    void move_up();
    void move_down();
    void move_left();
    void move_right();

    void set_target(const glm::vec2& target);

private:
    glm::vec3 target_pos;
};

#endif // __SPACESHIP_H_
