#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow &window,
                        texture_holder &textures,
                        font_holder &fonts,
                        Player &player)
    : window(&window), textures(&textures),
      fonts(&fonts), player(&player) {}

State::State(StateStack &stack, Context context)
    : stack(&stack), context(context) {}

void State::request_stack_push(States::ID state_id)
{
  stack->push_state(state_id);
}
void State::request_stack_pop()
{
  stack->pop_state();
}
void State::request_stack_clear()
{
  stack->clear_states();
}

State::Context State::get_context() const { return context; }
