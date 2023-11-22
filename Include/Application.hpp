#if !defined(APPLICATION_H)
#define APPLICATION_H

#include "ResourceHolder.hpp"
#include "Player.hpp"
#include "StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <exception>
#include <chrono>
#include <fstream>
#include <iomanip>

class Application : private sf::NonCopyable
{
public:
    Application();
    void run();

    ~Application();

private:
    void process_input();
    void update(sf::Time dt);
    void render();

    void update_statistics(sf::Time dt);
    void register_states();

    void write_crash_report(const std::exception &e);

private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow window;
    texture_holder textures;
    font_holder fonts;
    Player player;

    StateStack state_stack;

    sf::Text statistics_text;
    sf::Time statistics_update_time;
    std::size_t statistics_num_frames;

    bool update_gui = true;
    bool a = false;
};

#endif // APPLICATION_H
