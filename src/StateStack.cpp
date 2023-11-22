#include "StateStack.hpp"

StateStack::StateStack(State::Context context)
    : stack(), pending_list(), context(context), factories() {}


State::Ptr StateStack::create_state(States::ID state_id)
{
    auto found = factories.find(state_id);
    assert(found != factories.end());
    return found->second();
}

void StateStack::handle_event(const sf::Event &ev)
{
    /*
    In this for loop, you can verify that we iterate the active stack from the end to the
    beginning, in other words, from the highest state to the lowest. And, if any of the
    states returns false in its handleEvent() method, the loop is immediately ended.
    This gives the control to the states that may not want to let input flow to other states
    than itself.
    */
    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
        if (!(*itr)->handle_event(ev))
            break;
    apply_pending_changes();
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
        if (!(*itr)->update(dt))
            break;
    apply_pending_changes();
}

void StateStack::draw()
{
    // Renders all active states from top to bottom.
    for (State::Ptr &state : stack)
        state->draw();
}

void StateStack::apply_pending_changes()
{
    for (PendingChange change : pending_list)
    {
        switch (change.action)
        {
        case Action::Push:
            stack.push_back(create_state(change.state_id));
            break;
        case Action::Pop:
            stack.pop_back();
            break;
        case Action::Clear:
            stack.clear();
            break;
        }
    }
    pending_list.clear();
}

void StateStack::push_state(States::ID state_id)
{
    pending_list.push_back(PendingChange(Action::Push, state_id));
}
void StateStack::pop_state()
{
    pending_list.push_back(PendingChange(Action::Pop));
}
void StateStack::clear_states()
{
    pending_list.push_back(PendingChange(Action::Clear));
}

bool StateStack::is_empty() const { return stack.empty(); }

StateStack::PendingChange::PendingChange(Action action, States::ID id)
    : action(action), state_id(id) {}