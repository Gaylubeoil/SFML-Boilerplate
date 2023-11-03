#include "Utility.hpp"
#include "Animation.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cassert>
#include <chrono>
#include <random>

#define MATH_PI 3.141592653589793238462643383f

namespace
{
    std::default_random_engine createRandomEngine()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }

    auto random_engine = createRandomEngine();
}

float to_radian(const float degree)
{
    return MATH_PI / 180.f * degree;
}
float to_degree(const float radian)
{
    return 180.f / MATH_PI * radian;
}

void center_origin(Animation &animation)
{
    // sf::FloatRect bounds = animation.get_local_bounds();
    // animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
    //                     std::floor(bounds.top + bounds.height / 2.f));
}

void center_origin(sf::Text &text)
{
    /*
    The std::floor() function is used in the given code to ensure that
    the origin of the sf::Text object is set to integer coordinates,
    typically to ensure pixel-perfect rendering.
    */
    text.setOrigin(
        std::floor(text.getLocalBounds().left + text.getLocalBounds().width / 2.f),
        std::floor(text.getLocalBounds().top + text.getLocalBounds().height / 2.f));
}

void center_origin(sf::Sprite &sprite)
{
    sprite.setOrigin(
        std::floor(sprite.getLocalBounds().left + sprite.getLocalBounds().width / 2.f),
        std::floor(sprite.getLocalBounds().top + sprite.getLocalBounds().height / 2.f));
}

float length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unit_vector(sf::Vector2f vector)
{
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}

int random_int(int exclusive_max)
{
    std::uniform_int_distribution<> distr(0, exclusive_max - 1);
    return distr(random_engine);
}

std::string to_string(const sf::Keyboard::Key key)
{
#define KEY_TO_STRING(KEY)  \
    case sf::Keyboard::KEY: \
        return #KEY;

    switch (key)
    {
        KEY_TO_STRING(Unknown)
        KEY_TO_STRING(A)
        KEY_TO_STRING(B)
        KEY_TO_STRING(C)
        KEY_TO_STRING(D)
        KEY_TO_STRING(E)
        KEY_TO_STRING(F)
        KEY_TO_STRING(G)
        KEY_TO_STRING(H)
        KEY_TO_STRING(I)
        KEY_TO_STRING(J)
        KEY_TO_STRING(K)
        KEY_TO_STRING(L)
        KEY_TO_STRING(M)
        KEY_TO_STRING(N)
        KEY_TO_STRING(O)
        KEY_TO_STRING(P)
        KEY_TO_STRING(Q)
        KEY_TO_STRING(R)
        KEY_TO_STRING(S)
        KEY_TO_STRING(T)
        KEY_TO_STRING(U)
        KEY_TO_STRING(V)
        KEY_TO_STRING(W)
        KEY_TO_STRING(X)
        KEY_TO_STRING(Y)
        KEY_TO_STRING(Z)
        KEY_TO_STRING(Num0)
        KEY_TO_STRING(Num1)
        KEY_TO_STRING(Num2)
        KEY_TO_STRING(Num3)
        KEY_TO_STRING(Num4)
        KEY_TO_STRING(Num5)
        KEY_TO_STRING(Num6)
        KEY_TO_STRING(Num7)
        KEY_TO_STRING(Num8)
        KEY_TO_STRING(Num9)
        KEY_TO_STRING(Escape)
        KEY_TO_STRING(LControl)
        KEY_TO_STRING(LShift)
        KEY_TO_STRING(LAlt)
        KEY_TO_STRING(LSystem)
        KEY_TO_STRING(RControl)
        KEY_TO_STRING(RShift)
        KEY_TO_STRING(RAlt)
        KEY_TO_STRING(RSystem)
        KEY_TO_STRING(Menu)
        KEY_TO_STRING(LBracket)
        KEY_TO_STRING(RBracket)
        KEY_TO_STRING(SemiColon)
        KEY_TO_STRING(Comma)
        KEY_TO_STRING(Period)
        KEY_TO_STRING(Quote)
        KEY_TO_STRING(Slash)
        KEY_TO_STRING(BackSlash)
        KEY_TO_STRING(Tilde)
        KEY_TO_STRING(Equal)
        KEY_TO_STRING(Dash)
        KEY_TO_STRING(Space)
        KEY_TO_STRING(Return)
        KEY_TO_STRING(BackSpace)
        KEY_TO_STRING(Tab)
        KEY_TO_STRING(PageUp)
        KEY_TO_STRING(PageDown)
        KEY_TO_STRING(End)
        KEY_TO_STRING(Home)
        KEY_TO_STRING(Insert)
        KEY_TO_STRING(Delete)
        KEY_TO_STRING(Add)
        KEY_TO_STRING(Subtract)
        KEY_TO_STRING(Multiply)
        KEY_TO_STRING(Divide)
        KEY_TO_STRING(Left)
        KEY_TO_STRING(Right)
        KEY_TO_STRING(Up)
        KEY_TO_STRING(Down)
        KEY_TO_STRING(Numpad0)
        KEY_TO_STRING(Numpad1)
        KEY_TO_STRING(Numpad2)
        KEY_TO_STRING(Numpad3)
        KEY_TO_STRING(Numpad4)
        KEY_TO_STRING(Numpad5)
        KEY_TO_STRING(Numpad6)
        KEY_TO_STRING(Numpad7)
        KEY_TO_STRING(Numpad8)
        KEY_TO_STRING(Numpad9)
        KEY_TO_STRING(F1)
        KEY_TO_STRING(F2)
        KEY_TO_STRING(F3)
        KEY_TO_STRING(F4)
        KEY_TO_STRING(F5)
        KEY_TO_STRING(F6)
        KEY_TO_STRING(F7)
        KEY_TO_STRING(F8)
        KEY_TO_STRING(F9)
        KEY_TO_STRING(F10)
        KEY_TO_STRING(F11)
        KEY_TO_STRING(F12)
        KEY_TO_STRING(F13)
        KEY_TO_STRING(F14)
        KEY_TO_STRING(F15)
        KEY_TO_STRING(Pause)
    }
    return "";
}
