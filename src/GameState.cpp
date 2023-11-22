#include "GameState.hpp"

GameState::GameState(StateStack &stack,
                     Context context)
    : State(stack, context),
      world(context),
      player(*context.player),
      queue(world.get_command_queue())
{
}

void GameState::draw()
{
    world.draw();
}

bool GameState::update(sf::Time dt)
{
    world.update(dt);

    player.handle_realtime_input(queue);
    return true;
}

bool GameState::handle_event(const sf::Event &ev)
{
    if (ev.type != sf::Event::KeyPressed)
        return false;

    player.handle_event(ev, queue);
    return true;
}