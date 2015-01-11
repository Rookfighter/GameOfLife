#include <easylogging++.h>
#include "ui/ControlPanel.hpp"

#define THEME_CONFIG_FILE "res/widgets/Black.conf"

namespace gol
{

    ControlPanel::ControlPanel(World& world, GameLoop& gameLoop, tgui::Gui &gui)
            : world_(world), gameLoop_(gameLoop), gui_(gui), baseUpdateInterval_()
    {

    }

    ControlPanel::~ControlPanel()
    {
    }

    void ControlPanel::playButtonClicked()
    {
        //LOG(DEBUG)<< "Play Button clicked";

        tgui::Panel::Ptr panel = gui_.get("ControlPanel");
        tgui::Button::Ptr playButton = panel->get("PlayButton");
        tgui::Button::Ptr pauseButton = panel->get("PauseButton");

        playButton->disable();
        playButton->hide();
        pauseButton->enable();
        pauseButton->show();
        gameLoop_.resume();
    }

    void ControlPanel::pauseButtonClicked()
    {
        //LOG(INFO)<< "Pause Button clicked";

        tgui::Panel::Ptr panel = gui_.get("ControlPanel");
        tgui::Button::Ptr playButton = panel->get("PlayButton");
        tgui::Button::Ptr pauseButton = panel->get("PauseButton");

        pauseButton->disable();
        pauseButton->hide();
        playButton->enable();
        playButton->show();
        gameLoop_.pause();
    }

    void ControlPanel::resetButtonClicked()
    {
        //LOG(INFO)<< "Reset Button clicked";
        world_.reset();
    }

    void ControlPanel::speedSliderMoved()
    {
        //LOG(INFO)<<"Speed Slider moved";

        tgui::Panel::Ptr panel = gui_.get("ControlPanel");
        tgui::Slider::Ptr speedSlider = panel->get("SpeedSlider");
        tgui::Label::Ptr speedLabel = panel->get("SpeedLabel");

        float speed = 1;
        for(unsigned int i = 1; i < speedSlider->getValue(); ++i)
            speed *= 2;

        if(speedSlider->getValue() == 0)
            speed = 0.5;
        std::stringstream ss;
        ss.precision(1);
        ss << "Speed " << std::fixed << speed << "x";
        speedLabel->setText(ss.str());
        sf::Time interval = baseUpdateInterval_ * (1 / speed);
        gameLoop_.setUpdateInterval(interval);
    }

    void ControlPanel::init()
    {
        baseUpdateInterval_ = gameLoop_.getUpdateInterval();
        sf::Vector2f buttonPos, labelPos, sliderPos;
        sf::Vector2f buttonSize;
        float interWidgetSpace;

        tgui::Panel::Ptr panel(gui_, "ControlPanel");
        panel->setSize(gui_.getSize().x, gui_.getSize().y / 12);
        panel->setPosition(0, gui_.getSize().x - panel->getSize().y);

        buttonSize.x = gui_.getSize().x / 8;
        buttonSize.y = panel->getSize().y * 0.75;
        interWidgetSpace = (panel->getSize().y - buttonSize.y);

        tgui::Button::Ptr playButton(*panel, "PlayButton");
        playButton->load(THEME_CONFIG_FILE);
        playButton->setSize(buttonSize.x, buttonSize.y);
        buttonPos.x = interWidgetSpace / 2;
        buttonPos.y = buttonPos.x;
        playButton->setPosition(buttonPos);
        playButton->setText("Play");
        playButton->bindCallback(&ControlPanel::playButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Button::Ptr pauseButton(*panel, "PauseButton");
        pauseButton->load(THEME_CONFIG_FILE);
        pauseButton->setSize(buttonSize.x, buttonSize.y);
        pauseButton->setPosition(buttonPos);
        pauseButton->setText("Pause");
        pauseButton->disable();
        pauseButton->hide();
        pauseButton->bindCallback(&ControlPanel::pauseButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Button::Ptr resetButton(*panel, "ResetButton");
        resetButton->load(THEME_CONFIG_FILE);
        resetButton->setSize(buttonSize.x, buttonSize.y);
        buttonPos.x += buttonSize.x + interWidgetSpace;
        resetButton->setPosition(buttonPos);
        resetButton->setText("Reset");
        resetButton->bindCallback(&ControlPanel::resetButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Label::Ptr speedLabel(*panel, "SpeedLabel");
        speedLabel->load(THEME_CONFIG_FILE);
        speedLabel->setText("Speed 1.0x");
        labelPos.y = (panel->getSize().y - speedLabel->getSize().y) / 2;
        labelPos.x = buttonPos.x + buttonSize.x + interWidgetSpace;
        speedLabel->setPosition(labelPos);
        speedLabel->setTextColor(sf::Color::Black);

        tgui::Slider::Ptr speedSlider(*panel, "SpeedSlider");
        speedSlider->load(THEME_CONFIG_FILE);
        speedSlider->setSize(panel->getSize().x / 3, panel->getSize().y / 2.5);
        speedSlider->setVerticalScroll(false);
        speedSlider->setValue(1);
        speedSlider->setMinimum(0);
        speedSlider->setMaximum(4);
        sliderPos.y = (panel->getSize().y - speedSlider->getSize().y) / 2;
        sliderPos.x = labelPos.x + speedLabel->getSize().x
                + 2 * interWidgetSpace;
        speedSlider->setPosition(sliderPos);
        speedSlider->bindCallback(&ControlPanel::speedSliderMoved, this,
                tgui::Slider::ValueChanged);

    }
}
