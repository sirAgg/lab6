#include "ModelShape.h"

#include "Game.h"


SDL_Point temp_workspace[100];

ModelShape::ModelShape(Point2D pos, Color color, const Model* model)
    :Shape3D(pos, color), model(model)
{
    model_mat = glm::mat4(1.0f);
}

void ModelShape::render(SDL_Renderer* renderer)
{
    // get projection-view matrix and combine it with the model matrix
    glm::mat4 entire_trans_mat = *Game::get_game()->get_pv_mat() * model_mat;

    //SDL_Point* points = new SDL_Point[model->n_points];

    // apply the entire transformation matrix to each 
    // point to get the point's screen-coordinates
    for (int i = 0; i < model->n_points; i++)
    {
        glm::vec4 pos = entire_trans_mat * glm::vec4( model->points[i], 1.0f );
        pos /= pos.w;
        temp_workspace[i] = {(int)pos.x,(int)pos.y};
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // draw lines between the points
    for(int i = 0; i < model->n_lines; i++)
    {
        SDL_Point& p1 = temp_workspace[model->lines[i].a];
        SDL_Point& p2 = temp_workspace[model->lines[i].b];
        SDL_RenderDrawLine( renderer,
                            p1.x + (int)position.get_x(),
                            p1.y + (int)position.get_y(),
                            p2.x + (int)position.get_x(),
                            p2.y + (int)position.get_y()
        );
    }

    //delete[] points;
}
