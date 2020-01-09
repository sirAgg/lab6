#ifndef __HEALTHASTEROID_H_
#define __HEALTHASTEROID_H_

#include "Asteroid.h"

class HealthAsteroid : public Asteroid
{
public:
    HealthAsteroid( Point2D pos, glm::vec3 rotation_axis, float speed, float rotation_speed, float stop_position, float fade_distance);

    void when_killed() override;
};

#endif // __HEALTHASTEROID_H_
