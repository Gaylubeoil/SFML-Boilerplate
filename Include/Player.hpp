#if !defined(PLAYER_H)
#define PLAYER_H
#include "CommandQueue.hpp"
#include <SFML/Window.hpp>
#include <map>

class Player
{
public:
    enum class Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Attack,

        Count,
    };

    Player();

    void assign_key(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key get_assigned_key(Action action) const;

    void handle_event(const sf::Event &ev, CommandQueue &commands);
    void handle_realtime_input(CommandQueue &commands);

private:
    void initialize_keybinds();
    void initialize_actions();
    static bool is_realtime_action(Action action);

private:
    std::map<sf::Keyboard::Key, Action> key_binding;
    std::map<Action, Command> action_binding;
};

#endif // PLAYER_H
