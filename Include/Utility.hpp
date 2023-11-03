#if !defined(UTILITY_H)
#define UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>
#include <string>
#include <cmath>

namespace sf
{
    class Sprite;
    class Text;
}
class Animation;

// Convert sf::Keyboard::Key enumerator to a string.
std::string to_string(const sf::Keyboard::Key key);

float to_radian(const float degree);
float to_degree(const float radian);

void center_origin(sf::Sprite &sprite);
void center_origin(sf::Text &text);
void center_origin(Animation& animation);

float length (sf::Vector2f vector);
sf::Vector2f unit_vector(sf::Vector2f vector);

int random_int(int exclusive_max);

template <typename T>
std::string to_sting(const T &value);
#include "Utility.inl"

#endif // UTILITY_H
