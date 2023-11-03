#if !defined(COMMAND_H)
#define COMMAND_H

#include "Category.hpp"
#include <functional>
#include <SFML/System.hpp>
#include <iostream>
#include <assert.h>

/*
int add(int a, int b) { return a + b };
std::function<int(int, int)> adder1 = &add;
std::function<int(int, int)> adder2
= [] (int a, int b) { return a + b; };
*/

/*
In the earlier example, we can fix the second argument to 1 and thus have a new
function that takes only one argument. The placeholder _1 expresses that the first
argument is forwarded, while the second argument is bound to the constant 1:
std::function<int(int)> increaser = std::bind(&add, _1, 1);
int increased = increaser(5); // same as add(5, 1)
*/

class SceneNode;
struct Command
{
    Command() : action(), category(Category::Type::None) {}
    std::function<void(SceneNode &, sf::Time)> action;
    /**
     * @brief This variable is missing type safety.
     * Only objects of type Category::Type are supposed to be held by it.
     *
     */
    unsigned int category;
};

/**
 * @brief Lambda syntax:
 * [capture](parameters) -> return_type { body }
 *
 *  capture: Specifies which variables from the enclosing scope the lambda should have access to.
 *  parameters: The parameters the lambda function takes.
 *  return_type: The return type of the lambda function.
 *  body: The code that makes up the body of the lambda function.
 *
 */

/*
    Returns a function with return type void that has two parameters:
        - SceneNode&
        - sf::Time

    The returned function actsdifferently according to the 'Function' parameter passed.
*/
template <typename GameObject, typename Function>
std::function<void(SceneNode &, sf::Time)> derived_action(Function fn)
{
    /*
        [=] - Take all variables by value.
        () - (SceneNode &node, sf::Time dt) Parameters.
        -> void - return type.
        {} - Body. Makes an assertion and calls the template function.

    */
    return [=](SceneNode &node, sf::Time dt) -> void
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject *>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject &>(node), dt);
    };
}

#endif // COMMAND_H
