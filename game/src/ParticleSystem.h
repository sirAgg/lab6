#ifndef __PARTICLESYSTEM_H_
#define __PARTICLESYSTEM_H_

#include "GameObject.h"
#include "Model.h"

class ParticleSystem : public GameObject
{
public:
    ParticleSystem(Point2D pos, Color color, glm::vec3* velocities, int n_particles, glm::vec3 rotation_axis, float rotation, int life_length, int fade_out_time);
    ParticleSystem(Point2D pos, Color color, Model* model, glm::vec3 rotation_axis, float rotation, int life_length, int fade_out_time);

    bool update() override;
	void update_model_mat() override;

private:
    int life_time = 0;
    int life_length; 
    int fade_out_time;

	glm::vec3 rotation_axis;
	float rotation;
    Color color;
};

#endif /* __PARTICLESYSTEM_H_ */
