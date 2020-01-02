#ifndef __SPACE_SHIP_MODEL_H_
#define __SPACE_SHIP_MODEL_H_

#include "../Model.h"

glm::vec3 space_ship_model_points[] = {
    {0.000000, 0.000000, 1.368844},
    {1.000000, 1.000000, -1.224207},
    {-1.000000, 1.000000, -1.224207},
    {1.000000, -1.000000, -1.224207},
    {-1.000000, -1.000000, -1.224207},
    {0.469595, 0.000000, -0.611818},
    {0.000000, 0.469595, -0.611818},
    {-0.469595, 0.000000, -0.611818},
    {0.000000, -0.469595, -0.611818},
};
Line space_ship_model_lines[] = {
    {5, 3},
    {6, 1},
    {7, 2},
    {8, 4},
    {0, 1},
    {3, 0},
    {1, 5},
    {2, 6},
    {4, 7},
    {3, 8},
    {4, 0},
    {2, 0},
};
Model space_ship_model = { (glm::vec3*)&space_ship_model_points, 9, (Line*)&space_ship_model_lines, 12};

#endif