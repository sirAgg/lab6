#ifndef __GAMEOBJ_H_
#define __GAMEOBJ_H_

#include "glm/glm.hpp"

#include "ModelShape.h"

class GameObject
{
public:
    GameObject(glm::vec3 pos, ModelShape* shape);
    virtual void update() = 0;
    virtual void update_model_mat();

protected:
    glm::vec3 position;
    ModelShape* shape;
};


#endif // __GAMEOBJ_H_
