#ifndef __ASTEROID_H_
#define __ASTEROID_H_

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid( Point2D pos, glm::vec3 rotation_axis, float speed, float rotation_speed, float stop_position, float fade_distance);

    bool update() override;
    virtual void when_killed();
    void update_model_mat() override;
    void take_damage();

protected:
    glm::vec3 rotation_axis;
    float rotation;
    float rotation_speed;
    float speed;

    int health;

    Color color;
};

#endif // __ASTEROID_H_
