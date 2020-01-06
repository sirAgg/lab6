#ifndef __SPACESHIP_H_
#define __SPACESHIP_H_

#include "GameObject.h"
#include "ModelShape.h"
#include "InputActions.h"


class SpaceShip : public GameObject
{
public:
    SpaceShip(Point2D pos, ModelShape* shape);

    bool update() override;
    void update_model_mat() override;
    void input_update(InputActions input);


    void set_target(const glm::vec2& target);

private:
    float target_x;
    int shooting_cooldown = 0;
};

#endif // __SPACESHIP_H_
