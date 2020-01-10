#ifndef __MODEL_H_
#define __MODEL_H_

#include "glm/glm.hpp"

struct Line
{
    int a,b;
};

//
// Just a container of data 
// for static models
//
struct Model
{
    glm::vec3* points;
    int n_points;
    Line* lines;
    int n_lines;
};

#endif // __MODEL_H_
