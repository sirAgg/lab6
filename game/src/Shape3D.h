#ifndef __SHAPE3D_H_
#define __SHAPE3D_H_

#include "glm/glm.hpp"

#include "Shape.h"

//
// A shape rendered as a 3D wireframe
// the position from Shape it's not related to the position in 3d space 
// but is instead used to offset the rendered 3D wireframe.
// The set_model_mat function should be used to set the shapes 
// position (and rotation, and scale ...) in 3d space  
//
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
