#include "Shape3D.h"

Shape3D::Shape3D(Point2D pos, Color color)
    :Shape(pos,color)
{

}

void Shape3D::set_model_mat(glm::mat4 mat)
{
    model_mat = mat;
}
