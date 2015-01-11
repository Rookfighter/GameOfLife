#ifndef GOL_GAMEWINDOW_HPP
#define GOL_GAMEWINDOW_HPP

#include <TGUI/TGUI.hpp>
#include "logic/World.hpp"

namespace gol
{
    class GameWindow
    {
    private:
        World &world_;
        sf::RenderWindow window_;
        tgui::Gui gui_;

        void playButtonClicked();
        void pauseButtonClicked();
        void resetButtonClicked();
        void speedSliderMoved();
    public:
        GameWindow(World &world);
        ~GameWindow();

        bool isOpen() const;

        void redraw();
        void processInput();
    };

}

#endif
