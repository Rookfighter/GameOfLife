#ifndef GOL_GAMEWINDOW_HPP
#define GOL_GAMEWINDOW_HPP

#include <TGUI/TGUI.hpp>
#include "app/GameLoop.hpp"
#include "ui/ControlPanel.hpp"
#include "logic/World.hpp"

namespace gol
{
    class GameWindow
    {
    private:
        World &world_;
        GameLoop &gameLoop_;
        sf::RenderWindow window_;
        tgui::Gui gui_;
        ControlPanel controlPanel_;
        sf::View gameView_;
        bool scroll_;
        int zoomTicks_;
        sf::Vector2i lastPos_;

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
