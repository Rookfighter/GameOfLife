#include <easylogging++.h>
#include "ui/GameWindow.hpp"

#define WINDOW_TITLE "Game of Life"
#define DEF_WIDTH 800
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
                    gameLoop_, gui_), gameMenu_(world_, gameLoop_, gui_), gameView_(
                    window_.getDefaultView()), guiView_(
                    window_.getDefaultView()), scroll_(false), zoomTicks_(0)
    {
    }

    GameWindow::~GameWindow()
    {
    }

    void GameWindow::init()
    {
        gui_.setGlobalFont(FONT_FILE);

        tgui::Label::Ptr fpsLabel(gui_, "FPSLabel");
        fpsLabel->setText("00.0 FPS");
        fpsLabel->setTextColor(sf::Color::White);
        fpsLabel->setPosition(window_.getSize().x - fpsLabel->getSize().x, 20);

        controlPanel_.init();
        gameMenu_.init();
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

        window_.setView(guiView_);
        gui_.draw(false);
        window_.display();
    }

    void GameWindow::processInput()
    {
        sf::Event event;
        while(window_.pollEvent(event)) {
            if(isAllowedToHandleInput())
                handleInput(event);

            if(event.type == sf::Event::Closed) {
                window_.close();
            } else if(event.type == sf::Event::Resized) {
                sf::Vector2f newSize(event.size.width, event.size.height);

                gameView_.setSize(newSize);
                guiView_.setSize(newSize);
                guiView_.setCenter(((float) event.size.width) / 2,
                        ((float) event.size.height) / 2);

                tgui::Label::Ptr fpsLabel = gui_.get("FPSLabel");
                fpsLabel->setPosition(window_.getSize().x - fpsLabel->getSize().x, 20);
            }

            controlPanel_.handleEvent(event);
            gameMenu_.handleEvent(event);
            gui_.handleEvent(event, false);
        }
    }

    void GameWindow::handleInput(const sf::Event &event)
    {
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                scroll_ = true;
                lastPos_.x = event.mouseButton.x;
                lastPos_.y = event.mouseButton.y;
            }
        } else if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Left)
                scroll_ = false;
        } else if(event.type == sf::Event::MouseMoved) {
            if(scroll_) {
                sf::Vector2f last = window_.mapPixelToCoords(lastPos_,
                        gameView_);
                sf::Vector2f curr = window_.mapPixelToCoords(
                        sf::Vector2i(event.mouseMove.x, event.mouseMove.y),
                        gameView_);
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
            gameView_.zoom(zoomFac);
        }
    }

    bool GameWindow::isAllowedToHandleInput() const
    {
        return !gameMenu_.hasOpenDialog() && !controlPanel_.mouseEntered();
    }

}
