#include "ModelShape.h"

ModelShape::ModelShape(Point2D pos, Color color, Model* model, glm::mat4* pv_mat)
    :Shape(pos, color), model(model), pv_mat(pv_mat)
{
    model_mat = glm::mat4(1.0f);
}

void ModelShape::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point* points = new SDL_Point[model->n_points];

    glm::mat4 entire_trans_mat = *pv_mat * model_mat;

    for (int i = 0; i < model->n_points; i++)
    {
        glm::vec4 pos = entire_trans_mat * glm::vec4( model->points[i], 1.0f );
        pos /= pos.w;
        points[i] = {(int)pos.x,(int)pos.y};
    }

    for(int i = 0; i < model->n_lines; i++)
    {
        SDL_Point& p1 = points[model->lines[i].a];
        SDL_Point& p2 = points[model->lines[i].b];
        SDL_RenderDrawLine( renderer,
                            p1.x + (int)position.get_x(),
                            p1.y + (int)position.get_y(),
                            p2.x + (int)position.get_x(),
                            p2.y + (int)position.get_y()
        );
    }

    delete[] points;
}

void ModelShape::set_projection_view_mat(glm::mat4* mat)
{
    pv_mat = mat;
}

void ModelShape::set_model_mat(glm::mat4 mat)
{
    model_mat = glm::mat4(mat);
}
