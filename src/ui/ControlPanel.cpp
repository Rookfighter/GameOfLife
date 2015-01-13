#include <easylogging++.h>
#include "ui/ControlPanel.hpp"

#define THEME_CONFIG_FILE "res/widgets/Black.conf"

namespace gol
{

    ControlPanel::ControlPanel(World& world, GameLoop& gameLoop, tgui::Gui &gui)
            : world_(world), gameLoop_(gameLoop), gui_(gui), baseUpdateInterval_(), mouseEntered_(false)
    {

    }

    ControlPanel::~ControlPanel()
    {
    }

    void ControlPanel::panelCallback(const tgui::Callback &callback)
    {
        if(callback.trigger == tgui::Panel::MouseEntered) {
            mouseEntered_ = true;
        } else if(callback.trigger == tgui::Panel::MouseLeft) {
            mouseEntered_ = false;
        }
    }


    void ControlPanel::playButtonClicked()
    {
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
        world_.reset();
    }

    void ControlPanel::speedSliderMoved()
    {
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
        sf::Vector2f windowSize(gui_.getSize());
        float interWidgetSpace;

        tgui::Panel::Ptr panel(gui_, "ControlPanel");
        panel->setSize(windowSize.x, windowSize.y / 12);
        panel->setPosition(0, windowSize.y - panel->getSize().y);
        panel->bindCallbackEx(&ControlPanel::panelCallback, this, tgui::Panel::MouseEntered | tgui::Panel::MouseLeft);

        buttonSize.x = windowSize.x / 8;
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

        panel->add(speedSlider_, "SpeedSlider");
        speedSlider_->load(THEME_CONFIG_FILE);
        speedSlider_->setSize(panel->getSize().x / 3, panel->getSize().y / 2.5);
        speedSlider_->setVerticalScroll(false);
        speedSlider_->setValue(1);
        speedSlider_->setMinimum(0);
        speedSlider_->setMaximum(4);
        sliderPos.y = (panel->getSize().y - speedSlider_->getSize().y) / 2;
        sliderPos.x = labelPos.x + speedLabel->getSize().x
                + 2 * interWidgetSpace;
        speedSlider_->setPosition(sliderPos);
        speedSlider_->bindCallback(&ControlPanel::speedSliderMoved, this,
                tgui::Slider::ValueChanged);
    }

    tgui::Panel::Ptr ControlPanel::getPanel()
    {
        return gui_.get("ControlPanel");
    }

    void ControlPanel::handleEvent(const sf::Event &event)
    {
        if(event.type == event.Resized) {
            tgui::Panel::Ptr panel = getPanel();
            panel->setSize(event.size.width, panel->getSize().y);
            panel->setPosition(0, ((float) event.size.height) - panel->getSize().y);
        }
    }

    bool ControlPanel::mouseEntered() const
    {
        return mouseEntered_;
    }
}
