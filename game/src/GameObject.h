#ifndef __GAMEOBJ_H_
#define __GAMEOBJ_H_

#include "glm/glm.hpp"

#include "Point2D.h"
#include "ModelShape.h"

class GameObject
{
public:
    GameObject(Point2D pos, ModelShape* shape);
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void update_model_mat();
    void render(SDL_Renderer* renderer);

    const Point2D& get_position() const;
    Shape* get_shape();

protected:
    Point2D position;
    ModelShape* shape;
};


#endif // __GAMEOBJ_H_
