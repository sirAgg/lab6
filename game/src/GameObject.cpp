#include "GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(Point2D pos, Shape3D* shape, float radius)
    :position(pos), shape(shape), radius(radius)
{}

GameObject::~GameObject()
{
    delete shape;
}

void GameObject::update_model_mat()
{
    // updates shape's model matrix taking only position into account
    shape->set_model_mat(glm::translate(glm::mat4(1.0f), glm::vec3(position.get_x(), position.get_y(), 0.0f)));
}

void GameObject::render(SDL_Renderer* renderer)
{
    // update the model mat before rendering
    update_model_mat();
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

float GameObject::get_radius() const
{
    return radius;
}

bool GameObject::is_colliding_with(const GameObject* other)
{
    // For collision every GameObject is regarded as a circle
    float x_diff = position.get_x() - other->get_position().get_x();
    float y_diff = position.get_y() - other->get_position().get_y();
    float combined_radius_squared = radius*radius + other->get_radius()*other->get_radius();
    return  combined_radius_squared > x_diff*x_diff + y_diff*y_diff;
}
