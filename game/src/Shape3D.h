#ifndef __SHAPE3D_H_
#define __SHAPE3D_H_

#include "glm/glm.hpp"

#include "Shape.h"

class Shape3D : public Shape
{
public:
    Shape3D(Point2D pos, Color color);

    void render(SDL_Renderer* renderer) = 0;

    void set_model_mat(glm::mat4 mat);

protected:
    
    glm::mat4 model_mat;
};

#endif /* __SHAPE3D_H_ */
