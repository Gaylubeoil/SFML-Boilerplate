#include "Player.hpp"

Player::Player() : key_binding(), action_binding()
{
    initialize_keybinds();
    initialize_actions();
    for (auto &pair : action_binding)
        pair.second.category = Category::Type::PlayerAircraft;
}

void Player::initialize_keybinds()
{
    key_binding[sf::Keyboard::Up] = Action::MoveUp;
    key_binding[sf::Keyboard::Down] = Action::MoveDown;
    key_binding[sf::Keyboard::Left] = Action::MoveLeft;
    key_binding[sf::Keyboard::Right] = Action::MoveRight;
    key_binding[sf::Keyboard::Space] = Action::Attack;
}
void Player::initialize_actions()
{
}

void Player::handle_event(const sf::Event &ev, CommandQueue &commands)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        auto found = key_binding.find(ev.key.code);
        if (found != key_binding.end() && !is_realtime_action(found->second))
        {
            commands.push(action_binding[found->second]);
        }
    }
}

void Player::handle_realtime_input(CommandQueue &commands)
{
    for (auto pair : key_binding)
    {

        if (sf::Keyboard::isKeyPressed(pair.first) && is_realtime_action(pair.second))
            commands.push(action_binding[pair.second]);
    }
}

bool Player::is_realtime_action(Action action)
{
    switch (action)
    {
    case Action::MoveLeft:
    case Action::MoveRight:
    case Action::MoveDown:
    case Action::MoveUp:
    case Action::Attack:
        return true;

    default:
        return false;
    }
}

void Player::assign_key(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto itr = key_binding.begin(); itr != key_binding.end();)
    {
        if (itr->second == action)
            key_binding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    key_binding[key] = action;
}

sf::Keyboard::Key Player::get_assigned_key(Action action) const
{
    for (auto &pair : key_binding)
        if (pair.second == action)
            return pair.first;
    return sf::Keyboard::Unknown;
}