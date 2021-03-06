#include "ParticleShape.h"

#include "Game.h"

ParticleShape::ParticleShape(Point2D pos, Color color, glm::vec3* velocities, int n_particles)
    :Shape3D(pos, color), velocities(velocities), n_particles(n_particles)
{
    time_factor = 1.0f;
}

void ParticleShape::render(SDL_Renderer* renderer)
{
    // get projection-view matrix and combine it with the model matrix
    glm::mat4 entire_trans_mat = *Game::get_game()->get_pv_mat() * model_mat;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // render all points
    for (int i = 0; i < n_particles; i++)
    {
        // calculate point from velocity and time and then multiply it with the projection-view-model matrix
        glm::vec4 pos = entire_trans_mat * glm::vec4( velocities[i]*time_factor, 1.0f );
        pos /= pos.w;
        SDL_RenderDrawPoint(renderer, (int)pos.x, (int)pos.y);
    }
}

void ParticleShape::set_time(float t)
{
    time_factor = t;
}


