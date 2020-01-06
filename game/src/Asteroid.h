#ifndef __ASTEROID_H_
#define __ASTEROID_H_

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid( Point2D pos, ModelShape* shape, glm::vec3 rotation_axis, float speed, float rotation_speed, float stop_position, float fade_distance);

    bool update() override;
    void update_model_mat() override;
    void take_damage();

private:
    glm::vec3 rotation_axis;
    float rotation;
    float rotation_speed;
    float speed;

    float start_position;
    float stop_position;
    float fade_distance;

    int health;
};

#endif // __ASTEROID_H_
