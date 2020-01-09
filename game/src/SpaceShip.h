#ifndef __SPACESHIP_H_
#define __SPACESHIP_H_

#include "GameObject.h"
#include "ModelShape.h"


class SpaceShip : public GameObject
{
public:
    SpaceShip(Point2D pos, int lives);

    bool update() override;
    void update_model_mat() override;

    int get_lives();

private:

    float target_x;
    int shooting_cooldown = 0;
    int invincibility_time = 0;
    int lives;
	Color color;
};

#endif // __SPACESHIP_H_
