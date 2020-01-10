#ifndef __GAMEOBJ_H_
#define __GAMEOBJ_H_

#include "Point2D.h"
#include "Shape3D.h"

//
// Base for all the objects in the game world.
// All gameobjects exists in a 2D plane but
// have shape thats rendered in 3D wireframe
// The shape of an GameObject is completly owned 
// by the GameObject
// All gameobjects hitboxes are circles
// If the update function returns false the GameObject is dead
//

class GameObject
{
public:
    GameObject(Point2D pos, Shape3D* shape, float radius);
    virtual ~GameObject();

    virtual bool update() = 0; // returns false is this GameObject is dead 
    virtual void update_model_mat(); // updates the modelshape for its shape
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
