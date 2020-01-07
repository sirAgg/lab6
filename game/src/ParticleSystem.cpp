#include "ParticleSystem.h"

#include <stdio.h>
#include <cmath>

#include "ParticleShape.h"


glm::vec3 ParticleSystem::circle_particles[] = {
    {1.0f,0.0f,0.0f},
    {-1.0f,0.0f,0.0f},
    {0.0f,0.0f,1.0f},
    {0.0f,0.0f,-1.0f},
    {cos(M_PI_4),0.0f,sin(M_PI_4)},
    {-cos(M_PI_4),0.0f,sin(M_PI_4)},
    {-cos(M_PI_4),0.0f,-sin(M_PI_4)},
    {cos(M_PI_4),0.0f,-sin(M_PI_4)},
};


ParticleSystem::ParticleSystem(Point2D pos, float radius, Color color, glm::vec3* velocities, int n_particles, int life_length, int fade_out_time)
    :GameObject(pos, new ParticleShape(Point2D(0,0),color,velocities, n_particles),radius), life_length(life_length), fade_out_time(fade_out_time), color(color)
{

}

bool ParticleSystem::update()
{
    if( life_time > life_length )
        return false;

    else if( life_time > fade_out_time )
    {
        float t = (float)(life_length - life_time)/(float)(life_length-fade_out_time);
        Color c = color.scale(t);
        shape->set_color(c);
    }

    ((ParticleShape*)shape)->set_time(life_time*0.08f);

    life_time++;
    return true;
}
