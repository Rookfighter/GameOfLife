#include <easylogging++.h>
#include "ui/GameWindow.hpp"

#define WINDOW_TITLE "Game of Life"
#define DEF_WIDTH 600
#define DEF_HEIGHT 600
#define THEME_CONFIG_FILE "res/widgets/Black.conf"
#define FONT_FILE "res/fonts/DejaVuSans.ttf"

namespace gol
{

    GameWindow::GameWindow(World &world)
            : world_(world), window_(sf::VideoMode(DEF_WIDTH, DEF_HEIGHT),
            WINDOW_TITLE), gui_(window_)
    {
        gui_.setGlobalFont(FONT_FILE);
        sf::Vector2f buttonPos, labelPos, sliderPos;
        sf::Vector2f buttonSize;
        float interWidgetSpace;

        tgui::Panel::Ptr botPanel(gui_, "Bottom Panel");
        botPanel->setSize(DEF_WIDTH, DEF_HEIGHT / 12);
        botPanel->setPosition(0, DEF_HEIGHT - botPanel->getSize().y);

        buttonSize.x = DEF_WIDTH / 8;
        buttonSize.y = botPanel->getSize().y * 0.75;

        tgui::Button::Ptr playButton(*botPanel, "Play Button");
        playButton->load(THEME_CONFIG_FILE);
        playButton->setSize(buttonSize.x, buttonSize.y);
        interWidgetSpace = (botPanel->getSize().y - buttonSize.y);
        buttonPos.x = interWidgetSpace / 2;
        buttonPos.y = buttonPos.x;
        playButton->setPosition(buttonPos);
        playButton->setText("Play");
        playButton->bindCallback(&GameWindow::playButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Button::Ptr pauseButton(*botPanel, "Pause Button");
        pauseButton->load(THEME_CONFIG_FILE);
        pauseButton->setSize(buttonSize.x, buttonSize.y);
        interWidgetSpace = (botPanel->getSize().y - buttonSize.y);
        pauseButton->setPosition(buttonPos);
        pauseButton->setText("Pause");
        pauseButton->disable();
        pauseButton->hide();
        pauseButton->bindCallback(&GameWindow::pauseButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Button::Ptr resetButton(*botPanel, "Reset Button");
        resetButton->load(THEME_CONFIG_FILE);
        resetButton->setSize(buttonSize.x, buttonSize.y);
        buttonPos.x += buttonSize.x + interWidgetSpace;
        resetButton->setPosition(buttonPos);
        resetButton->setText("Reset");
        resetButton->bindCallback(&GameWindow::resetButtonClicked, this,
                tgui::Button::LeftMouseClicked);

        tgui::Label::Ptr label(*botPanel, "Speed Label");
        label->load(THEME_CONFIG_FILE);
        label->setText("Speed 1.0x");
        labelPos.y = (botPanel->getSize().y - label->getSize().y) / 2;
        labelPos.x = buttonPos.x + buttonSize.x + interWidgetSpace;
        label->setPosition(labelPos);
        label->setTextColor(sf::Color::Black);

        tgui::Slider::Ptr slider(*botPanel, "Speed Slider");
        slider->load(THEME_CONFIG_FILE);
        slider->setSize(botPanel->getSize().x / 3,
                botPanel->getSize().y / 2.5);
        slider->setVerticalScroll(false);
        slider->setValue(1);
        slider->setMinimum(0);
        slider->setMaximum(4);
        sliderPos.y = (botPanel->getSize().y - slider->getSize().y) / 2;
        sliderPos.x = labelPos.x + label->getSize().x + 2 * interWidgetSpace;
        slider->setPosition(sliderPos);
        slider->bindCallback(&GameWindow::speedSliderMoved, this,
                tgui::Slider::ValueChanged);
    }

    void GameWindow::playButtonClicked()
    {
        LOG(INFO)<< "Play Button clicked";
        tgui::Button::Ptr playButton = gui_.get("Play Button", true);
        tgui::Button::Ptr pauseButton = gui_.get("Pause Button", true);
        playButton->disable();
        playButton->hide();
        pauseButton->enable();
        pauseButton->show();
        // unpause gameloop
    }

    void GameWindow::pauseButtonClicked()
    {
        LOG(INFO)<< "Pause Button clicked";
        tgui::Button::Ptr playButton = gui_.get("Play Button", true);
        tgui::Button::Ptr pauseButton = gui_.get("Pause Button", true);
        pauseButton->disable();
        pauseButton->hide();
        playButton->enable();
        playButton->show();
        // pause gameloop
    }

    void GameWindow::resetButtonClicked()
    {
        LOG(INFO)<< "Reset Button clicked";
        world_.reset();
    }

    void GameWindow::speedSliderMoved()
    {
        LOG(INFO)<< "Speed Slider moved";
        tgui::Slider::Ptr slider = gui_.get("Speed Slider", true);
        tgui::Label::Ptr label = gui_.get("Speed Label", true);

        float speed = 1;
        for(unsigned int i = 1; i < slider->getValue(); ++i)
            speed *= 2;

        if(slider->getValue() == 0)
            speed = 0.5;
        std::stringstream ss;
        ss.precision(1);
        ss << "Speed " << std::fixed << speed << "x";
        label->setText(ss.str());
        // make gameloop faster/slower
    }

    GameWindow::~GameWindow()
    {
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
