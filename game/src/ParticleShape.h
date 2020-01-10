#ifndef PARTICLESHAPE_H
#define PARTICLESHAPE_H

#include "glm/glm.hpp"

#include "Shape3D.h"

//
// Renders several points in 3D
// The points begin in the origin of the 
// particle shape and moves outvards with it's own velocities
// the time does not updates automaticly and has to be updated 
// with the set_time function
//
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
