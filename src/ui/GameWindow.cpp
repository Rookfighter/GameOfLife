#include <easylogging++.h>
#include "ui/GameWindow.hpp"

#define WINDOW_TITLE "Game of Life"
#define DEF_WIDTH 600
#define DEF_HEIGHT 600
#define THEME_CONFIG_FILE "res/widgets/Black.conf"
#define FONT_FILE "res/fonts/DejaVuSans.ttf"
#define ZOOM_PER_TICK 1.5

namespace gol
{
    GameWindow::GameWindow(World &world, GameLoop &gameLoop)
            : world_(world), gameLoop_(gameLoop), window_(
                    sf::VideoMode(DEF_WIDTH, DEF_HEIGHT),
                    WINDOW_TITLE), gui_(window_), controlPanel_(world_,
                    gameLoop_, gui_), gameView_(window_.getDefaultView()), scroll_(
                    false), zoomTicks_(0)
    {
    }

    GameWindow::~GameWindow()
    {
    }

    void GameWindow::init()
    {
        gui_.setGlobalFont(FONT_FILE);

        tgui::Label::Ptr fpsLabel(gui_, "FPSLabel");
        fpsLabel->setPosition(0, 0);
        fpsLabel->setText("00.0 FPS");
        fpsLabel->setTextColor(sf::Color::White);

        controlPanel_.init();
    }

    bool GameWindow::isOpen() const
    {
        return window_.isOpen();
    }

    void GameWindow::redraw()
    {
        std::stringstream ss;
        ss.precision(1);
        ss << std::fixed << gameLoop_.getFPS() << " FPS";
        tgui::Label::Ptr label = gui_.get("FPSLabel");
        label->setText(ss.str());

        window_.clear();
        window_.setView(gameView_);
        world_.draw(window_);

        window_.setView(window_.getDefaultView());
        gui_.draw();
        window_.display();
    }

    void GameWindow::processInput()
    {
        sf::Event event;
        while(window_.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window_.close();
            } else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    scroll_ = true;
                    lastPos_.x = event.mouseButton.x;
                    lastPos_.y = event.mouseButton.y;
                }
            } else if(event.type == sf::Event::Resized) {

            } else if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left)
                    scroll_ = false;
            } else if(event.type == sf::Event::MouseMoved) {
                if(scroll_) {
                    sf::Vector2f last = window_.mapPixelToCoords(lastPos_, gameView_);
                    sf::Vector2f curr = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), gameView_);
                    sf::Vector2f diff = last - curr;

                    gameView_.move(diff);
                    lastPos_.x = event.mouseMove.x;
                    lastPos_.y = event.mouseMove.y;
                }
            } else if(event.type == sf::Event::MouseWheelMoved) {
                float zoomFac = 1.0f;
                int zoomTicks = event.mouseWheel.delta;
                while(zoomTicks > 0) {
                    zoomFac /= ZOOM_PER_TICK;
                    --zoomTicks;
                }
                while(zoomTicks < 0) {
                    zoomFac *= ZOOM_PER_TICK;
                    ++zoomTicks;
                }
                //sf::Vector2f center = window_.mapPixelToCoords(sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y), gameView_);
                //gameView_.setCenter(center);
                gameView_.zoom(zoomFac);
            }

            gui_.handleEvent(event);
        }
    }

}
