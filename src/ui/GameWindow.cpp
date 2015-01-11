#include <easylogging++.h>
#include "ui/GameWindow.hpp"

#define WINDOW_TITLE "Game of Life"
#define DEF_WIDTH 600
#define DEF_HEIGHT 600
#define THEME_CONFIG_FILE "res/widgets/Black.conf"
#define FONT_FILE "res/fonts/DejaVuSans.ttf"

namespace gol
{
    GameWindow::GameWindow(World &world, GameLoop &gameLoop)
            : world_(world), gameLoop_(gameLoop), window_(sf::VideoMode(DEF_WIDTH, DEF_HEIGHT),
            WINDOW_TITLE), gui_(window_), controlPanel_(world_, gameLoop_, gui_)
    {

    }

    GameWindow::~GameWindow()
    {
    }

    void GameWindow::init()
    {
        gui_.setGlobalFont(FONT_FILE);
        controlPanel_.init();
    }

    bool GameWindow::isOpen() const
    {
        return window_.isOpen();
    }

    void GameWindow::redraw()
    {
        window_.clear();
        world_.draw(window_);
        gui_.draw();
        window_.display();
    }

    void GameWindow::processInput()
    {
        sf::Event event;
        while(window_.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window_.close();
            }

            gui_.handleEvent(event);
        }
    }

}
