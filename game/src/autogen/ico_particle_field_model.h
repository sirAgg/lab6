#ifndef __ICO_PARTICLE_FIELD_MODEL_H_
#define __ICO_PARTICLE_FIELD_MODEL_H_

#include "../Model.h"

static glm::vec3 ico_particle_field_model_points[] = {
    {0.000000, -1.000000, 0.000000},
    {0.723600, -0.447215, 0.525720},
    {-0.276385, -0.447215, 0.850640},
    {-0.894425, -0.447215, 0.000000},
    {-0.276385, -0.447215, -0.850640},
    {0.723600, -0.447215, -0.525720},
    {0.276385, 0.447215, 0.850640},
    {-0.723600, 0.447215, 0.525720},
    {-0.723600, 0.447215, -0.525720},
    {0.276385, 0.447215, -0.850640},
    {0.894425, 0.447215, 0.000000},
    {0.000000, 1.000000, 0.000000},
};
static Line ico_particle_field_model_lines[] = {{0,0}
};
Model GeneratedModels::ico_particle_field_model = { (glm::vec3*)&ico_particle_field_model_points, 12, (Line*)&ico_particle_field_model_lines, 0};

#endif
