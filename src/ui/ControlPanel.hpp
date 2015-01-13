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

        sf::Time baseUpdateInterval_;
        bool mouseEntered_;

        tgui::Slider::Ptr speedSlider_;

        void panelCallback(const tgui::Callback &callback);
        void playButtonClicked();
        void pauseButtonClicked();
        void resetButtonClicked();
        void speedSliderMoved();
        void speedSliderGrabbed();
    public:
        ControlPanel(World &world, GameLoop &gameLoop, tgui::Gui &gui);
        ~ControlPanel();

        tgui::Panel::Ptr getPanel();

        void init();
        void handleEvent(const sf::Event &event);
        bool mouseEntered() const;
    };

}

#endif
