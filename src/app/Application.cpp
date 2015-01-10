#include <iostream>
#include <easylogging++.h>
#include "app/Application.hpp"

#define WINDOW_TITLE "Game of Life"

namespace gol
{

    Application::Application()
            : world_(200, 200), gameLoop_(std::bind(&Application::update, this),
                    std::bind(&Application::redraw, this)), window_(
                    sf::VideoMode(600, 600), WINDOW_TITLE)
    {
        gameLoop_.setUpdateInterval(sf::milliseconds(100));
        world_.init(4000);
    }

    Application::~Application()
    {
    }

    void Application::update()
    {
        bool updateWorld = true;
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window_.close();
                gameLoop_.stop();
                updateWorld = false;
            }
        }

        if(updateWorld)
            world_.update();
    }

    void Application::redraw()
    {
        window_.clear();
        world_.draw(window_);
        window_.display();
    }

    int Application::run()
    {
        LOG(INFO) << "Started Game of Life";
        int exitCode = 0;

        try {
            gameLoop_.start();
        } catch (std::exception &e) {
            LOG(ERROR) << "Exception: " << e.what();
            exitCode = -1;
        } catch (...) {
            LOG(ERROR) << "Catched unknown instance";
            exitCode = -1;
        }
        LOG(INFO) << "Game of Life terminated";

        return exitCode;
    }

}
