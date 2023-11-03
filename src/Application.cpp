#include "Application.hpp"
#include "Utility.hpp"
#include "State.hpp"
#include "ResourceIdentifiers.hpp"
#include "GameState.hpp"
#include "ResourceIdentifiers.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);
Application::Application()
    : window(sf::VideoMode(320, 240), "Application", sf::Style::Close),
      textures(), fonts(), player(),
      state_stack(State::Context(window, textures, fonts, player)),
      statistics_text(), statistics_update_time(), statistics_num_frames(0)
{
    window.setKeyRepeatEnabled(false);
    fonts.load(Fonts::ID::Main, "../assets/fonts/Minecraft.ttf");

    statistics_text.setFont(fonts.get(Fonts::ID::Main));
    statistics_text.setCharacterSize(12u);
    statistics_text.setPosition(10.f, 10.f);

    register_states();
    state_stack.push_state(States::ID::Game);
}

void Application::register_states()
{
    state_stack.register_state<GameState>(States::ID::Game);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while (window.isOpen())
    {
        /* The hasFocus functions check whether the user is currently
        in the application's window or doing something else.*/
        if (window.hasFocus())
        {
            sf::Time elapsed_time = clock.restart();
            time_since_last_update += elapsed_time;
            while (time_since_last_update > TimePerFrame)
            {
                time_since_last_update -= TimePerFrame;
                process_input();
                update(TimePerFrame); // delta time
            }
            update_statistics(elapsed_time);
            render();
        }
    }
}

void Application::process_input()
{
    sf::Event ev;
    while (window.pollEvent(ev))
    {
        state_stack.handle_event(ev);
        if (ev.type == sf::Event::Closed || state_stack.is_empty())
            window.close();
    }
}

void Application::update(sf::Time dt)
{
    state_stack.update(dt);
}

void Application::render()
{
    window.clear();

    state_stack.draw();

    window.setView(window.getDefaultView());

    window.draw(statistics_text);
    window.display();
}

void Application::update_statistics(sf::Time dt)
{
    statistics_update_time += dt;
    statistics_num_frames += 1;
    if (statistics_update_time >= sf::seconds(1.0f))
    {
        statistics_text.setString("FPS: " + to_string(statistics_num_frames));

        statistics_update_time -= sf::seconds(1.0f);
        statistics_num_frames = 0;
    }
}

void Application::write_crash_report(const std::exception &e)
{
    // Parse current time into a string.
    auto now = std::chrono::system_clock::now();
    auto in_time = std::chrono::system_clock::to_time_t(now);
    auto time_string = std::put_time(std::localtime(&in_time), "%Y-%m-%d %X");

    std::ofstream error_file("Crash_Reports.txt", std::ios::out | std::ios::app);
    error_file << "Game crash at: " << time_string << '\n';
    error_file << e.what() << std::endl;
    error_file.close();
}