#include "HealthAsteroid.h"

HealthAsteroid::HealtAsteroid( Point2D pos, glm::vec3 rotation_axis, float speed, float rotation_speed, float stop_position, float fade_distance)
    :Asteroid(pos, rotation_axis, speed, rotation_speed, stop_position, fade_distance)
{
    color = 0x77FF77FF;
}
