#ifndef __MODEL_SHAPE_H_
#define __MODEL_SHAPE_H_

#include "Shape3D.h"
#include "Model.h"

class ModelShape : public Shape3D
{
public:
    ModelShape(Point2D pos, Color color, const Model* model);
    void render(SDL_Renderer* renderer);

private:
    const Model* model;
};

#endif // __MODEL_SHAPE_H_
