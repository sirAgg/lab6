#include "GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(Point2D pos, ModelShape* shape)
    :position(pos), shape(shape)
{}

GameObject::~GameObject()
{
    delete shape;
}

void GameObject::update_model_mat()
{
    // updates shapes model matrix taking only position into account
    shape->set_model_mat(glm::translate(glm::mat4(1.0f), glm::vec3(position.get_x(), position.get_y(), 0.0f)));
}

void GameObject::render(SDL_Renderer* renderer)
{
    shape->render(renderer);
}

const Point2D& GameObject::get_position() const
{
    return position;
}

Shape* GameObject::get_shape()
{
    return shape;
}
