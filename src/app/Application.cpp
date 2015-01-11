#include <iostream>
#include <easylogging++.h>
#include "app/Application.hpp"

namespace gol
{

    Application::Application()
    : world_(200, 200), gameLoop_(std::bind(&Application::update, this),
            std::bind(&GameWindow::redraw, &window_), std::bind(&Application::processInput, this)), window_(world_)
    {
        gameLoop_.setUpdateInterval(sf::milliseconds(100));
        world_.init(4000);
    }

    Application::~Application()
    {
    }

    void Application::processInput()
    {
        window_.processInput();
        if(!window_.isOpen())
            gameLoop_.stop();
    }

    void Application::update()
    {
        if(window_.isOpen())
            world_.update();
    }

    int Application::run()
    {
        LOG(INFO)<<"Started Game of Life";
    int exitCode = 0;

    try {
        gameLoop_.pause();
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
