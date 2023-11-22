#if !defined(STATE_H)
#define STATE_H
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include <memory>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow &window, texture_holder &textures, 
                font_holder &fonts, Player &player);

        sf::RenderWindow *window;
        texture_holder *textures;
        font_holder *fonts;
        Player *player;

    };

public:
    State(StateStack &stack, Context context);

    virtual void draw() = 0;
    virtual bool update(sf::Time) = 0;
    virtual bool handle_event(const sf::Event &ev) = 0;

    virtual ~State() = default;

protected:
    void request_stack_push(States::ID state_id);
    void request_stack_pop();
    void request_stack_clear();

    Context get_context() const;

private:
    StateStack *stack;
    Context context;
};

#endif // STATE_H
