#ifndef COMMAND_H
#define COMMAND_H

#include "Category.h"
#include "SFML/System/Time.hpp"
#include<functional>
#include<cassert>

class SceneNode;

struct Command
{
    Command();
    std::function<void(SceneNode&)> action;
    unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&)> derivedAction(Function fn)
{
    return [=] (SceneNode& node)
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node));
    };
}

template <typename GameObject, typename Function>
std::function<void(SceneNode&)> derivedAction(Function fn, unsigned int id)
{
    return [=] (SceneNode& node)
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node), id);
    };
}

#endif // COMMAND_H
