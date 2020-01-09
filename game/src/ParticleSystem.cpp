#include "ParticleSystem.h"

#include <stdio.h>
#include "glm/gtc/matrix_transform.hpp"

#include "ParticleShape.h"

ParticleSystem::ParticleSystem(Point2D pos, float radius, Color color, glm::vec3* velocities, int n_particles, glm::vec3 rotation_axis, float rotation, int life_length, int fade_out_time)
    :GameObject(pos, new ParticleShape(Point2D(0,0),color,velocities, n_particles),radius), rotation_axis(rotation_axis), rotation(rotation), life_length(life_length), fade_out_time(fade_out_time), color(color)
{

}
ParticleSystem::ParticleSystem(Point2D pos, float radius, Color color, Model* model, glm::vec3 rotation_axis, float rotation, int life_length, int fade_out_time)
    :ParticleSystem(pos, radius, color, model->points, model->n_points, rotation_axis, rotation, life_length, fade_out_time)
{}

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

void ParticleSystem::update_model_mat()
{
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(position.get_x(), position.get_y(), 0.0f));
    m = glm::rotate(m, rotation, rotation_axis);
    shape->set_model_mat(m);
}
