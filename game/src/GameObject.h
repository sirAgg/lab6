#ifndef __GAMEOBJ_H_
#define __GAMEOBJ_H_

#include "glm/glm.hpp"

#include "Point2D.h"
#include "Shape3D.h"

class GameObject
{
public:
    GameObject(Point2D pos, Shape3D* shape, float radius);
    virtual ~GameObject();

    virtual bool update() = 0;
    virtual void update_model_mat();
    void render(SDL_Renderer* renderer);

    const Point2D& get_position() const;
    Shape* get_shape();
    float get_radius() const;

    bool is_colliding_with(const GameObject* other);

protected:
    Point2D position;
    Shape3D* shape;
    float radius;
};


#endif // __GAMEOBJ_H_
