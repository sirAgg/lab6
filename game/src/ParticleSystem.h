#ifndef __PARTICLESYSTEM_H_
#define __PARTICLESYSTEM_H_

#include "GameObject.h"

class ParticleSystem : public GameObject
{
public:
    ParticleSystem(Point2D pos, float radius, Color color, glm::vec3* velocities, int n_particles, int life_length, int fade_out_time);

    bool update() override;

    static glm::vec3 circle_particles[];

private:
    const glm::vec3* velocities;
    int n_particles;
    int life_time = 0;
    int life_length; 
    int fade_out_time;

    Color color;
};

#endif /* __PARTICLESYSTEM_H_ */
