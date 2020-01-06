#ifndef __MODEL_SHAPE_H_
#define __MODEL_SHAPE_H_

#include "Shape.h"
#include "Model.h"

class ModelShape : public Shape
{
public:
    ModelShape(Point2D pos, Color color, const Model* model, glm::mat4* pv_mat);
    void render(SDL_Renderer* renderer);
    void set_projection_view_mat(glm::mat4* mat);

    void set_model_mat(glm::mat4 mat);

private:
    const Model* model;
    glm::mat4* pv_mat;
    glm::mat4 model_mat;
};

#endif // __MODEL_SHAPE_H_
