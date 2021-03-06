#ifndef GOL_GAMEWINDOW_HPP
#define GOL_GAMEWINDOW_HPP

#include <TGUI/TGUI.hpp>
#include "app/GameLoop.hpp"
#include "ui/ControlPanel.hpp"
#include "ui/GameMenu.hpp"
#include "ui/WindowState.hpp"
#include "logic/World.hpp"

namespace gol
{
    class GameWindow
    {
    private:
        WindowProperties properties_;
        GameLoop &gameLoop_;
        sf::RenderWindow window_;
        tgui::Gui gui_;
        ControlPanel controlPanel_;
        GameMenu gameMenu_;
        int zoomTicks_;

        WindowState *state_;

        bool isAllowedToHandleInput() const;
        void handleInput(const sf::Event &event);
    public:
        GameWindow(World &world, GameLoop &gameLoop);
        ~GameWindow();

        void init();

        bool isOpen() const;

        void redraw();
        void processInput();
    };

}

#endif
