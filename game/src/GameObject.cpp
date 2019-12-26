#include "GameObject.h"


#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(glm::vec3 pos, ModelShape* shape)
    :position(pos), shape(shape)
{}

void GameObject::update_model_mat()
{
    // updates shapes model matrix taking only position into account
    shape->set_model_mat(glm::translate(glm::mat4(1.0f), position));
}
