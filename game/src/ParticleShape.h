#ifndef PARTICLESHAPE_H
#define PARTICLESHAPE_H

#include "glm/glm.hpp"

#include "Shape3D.h"

class ParticleShape : public Shape3D
{
public:
    ParticleShape(Point2D pos, Color color, glm::vec3* velocities, int n_particles);

    void render(SDL_Renderer* renderer);

    void set_time(float t);


private:
    
    const glm::vec3* velocities;
    int n_particles;
    float time_factor;
};

#endif /* PARTICLESHAPE_H */
