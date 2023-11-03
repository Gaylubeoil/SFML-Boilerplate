#if !defined(GAME_STATE_H)
#define GAME_STATE_H

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

class GameState : public State
{
public:
    GameState(StateStack &stack,
              Context context);

    virtual void    draw() override;
    virtual bool    update(sf::Time dt) override;
    virtual bool    handle_event(const sf::Event &ev) override;

    virtual         ~GameState() = default;

private:
    World           world;
    Player&         player;
    CommandQueue&   queue;
};

#endif // GAME_STATE_H
