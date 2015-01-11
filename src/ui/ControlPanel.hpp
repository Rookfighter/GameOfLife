#ifndef GOL_CONTROLPANEL_HPP
#define GOL_CONTROLPANEL_HPP

#include <TGUI/TGUI.hpp>
#include "logic/World.hpp"
#include "app/GameLoop.hpp"

namespace gol
{

    class ControlPanel
    {
    private:
        World &world_;
        GameLoop &gameLoop_;
        tgui::Gui &gui_;

        sf::Time initUpdateInterval_;

        void playButtonClicked();
        void pauseButtonClicked();
        void resetButtonClicked();
        void speedSliderMoved();
    public:
        ControlPanel(World &world, GameLoop &gameLoop, tgui::Gui &gui);
        ~ControlPanel();

        void init();
    };

}

#endif
