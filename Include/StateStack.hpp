#if !defined(STATE_STACK_H)
#define STATE_STACK_H

#include "State.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <vector>
#include <map>
#include <functional>
#include <assert.h>

class StateStack : private sf::NonCopyable
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(State::Context context);

    template <typename T>
    void register_state(States::ID state_id);

    void handle_event(const sf::Event &ev);
    void update(sf::Time dt);
    void draw();

    void push_state(States::ID state_id);
    void pop_state();
    void clear_states();

    bool is_empty() const;

private:
    State::Ptr create_state(States::ID state_id);
    void apply_pending_changes();

private:
    struct PendingChange
    {
        PendingChange(Action action, States::ID id = States::ID::None);
        Action action;
        States::ID state_id;
    };

private:
    std::vector<State::Ptr> stack;
    std::vector<PendingChange> pending_list;
    State::Context context;
    std::map<States::ID, std::function<State::Ptr()>> factories;
};

template <typename T>
void StateStack::register_state(States::ID state_id)
{
    factories[state_id] = [this]()
    {
        // T is the derived state class we want to register
        return State::Ptr(new T(*this, context));
    };
    // This approach has the advantage that the StateStack
    // class doesn't need to know the concrete state classes,
    // we thus keep the dependencies low. For state classes
    // that take more than two parameters, we can write an overload
    // to pass an additional argument.
}

#endif // STATE_STACK_H
