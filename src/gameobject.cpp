#include "gameobject.h"

GameObject::GameObject(GameObject *parent) :
    parent_(parent)
{
    if (parent)
        parent->children_.push_back(this);
}

bool GameObject::event(const Event &event)
{
    for (const auto &child : children_)
    {
        if (child->processEvent(event))
            return true;
    }

    return processEvent(event);
}