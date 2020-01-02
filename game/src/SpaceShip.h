#ifndef __SPACESHIP_H_
#define __SPACESHIP_H_

#include "GameObject.h"
#include "ModelShape.h"
#include "InputActions.h"

const float MOVE_FACTOR= 0.1f;
const float TARGET_MOVE_SPEED = 0.15f;

class SpaceShip : public GameObject
{
public:
    SpaceShip(Point2D pos, ModelShape* shape);

    void update() override;
    void update_model_mat() override;
    void input_update(InputActions input);


    void set_target(const glm::vec2& target);

private:
    float target_x;
        unsigned char* input_map;
};

#endif // __SPACESHIP_H_
