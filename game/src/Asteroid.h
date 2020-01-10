#ifndef __ASTEROID_H_
#define __ASTEROID_H_

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid( Point2D pos, glm::vec3 rotation_axis, float speed);

    bool update() override;
    void update_model_mat() override;
    void take_damage();

protected:
    int health;
    float speed;

    float rotation; 
    glm::vec3 rotation_axis; // axis to rotate around

    Color color;
};

#endif // __ASTEROID_H_
