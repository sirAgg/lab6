#ifndef __ASTEROID_H_
#define __ASTEROID_H_

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid( Point2D pos, ModelShape* shape, glm::vec3 rotation_axis, float speed, float rotation_speed);

    void update() override;
    void update_model_mat() override;

private:
    glm::vec3 rotation_axis;
    float rotation;
    float rotation_speed;
    float speed;
};

#endif // __ASTEROID_H_
