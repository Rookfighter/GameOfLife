#include <easylogging++.h>
#include "ui/GameMenu.hpp"

#define THEME_CONFIG_FILE "res/widgets/Black.conf"

namespace gol
{

    GameMenu::GameMenu(World& world, GameLoop& gameLoop, tgui::Gui &gui)
            : world_(world), gameLoop_(gameLoop), gui_(gui), dialogOpen_(false)
    {

    }

    GameMenu::~GameMenu()
    {
    }

    tgui::MenuBar::Ptr GameMenu::getMenuBar()
    {
        return gui_.get("GameMenu");
    }

    void GameMenu::init()
    {
        tgui::MenuBar::Ptr menu(gui_, "GameMenu");
        menu->load(THEME_CONFIG_FILE);
        menu->setSize(gui_.getSize().x, 20);
        menu->addMenu("Edit");
        menu->addMenuItem("Edit", "Resize");
        menu->bindCallbackEx(&GameMenu::menuItemClicked, this, tgui::MenuBar::MenuItemClicked);

        menu->addMenu("Help");
        menu->addMenuItem("Help", "Controls");

        initResizeDialog();
        initControlsDialog();
    }

    void GameMenu::menuItemClicked(const tgui::Callback &callback)
    {
        if(callback.text == "Resize")
            openResizeDialog();
        else if(callback.text == "Controls")
            openControlsDialog();
    }

    void GameMenu::initResizeDialog()
    {
        sf::Vector2f dialogSize(300, 200);
        sf::Vector2f editSize(dialogSize.x / 2, dialogSize.y / 5);
        sf::Vector2f buttonSize(dialogSize.x / 3, dialogSize.y / 5);

        gui_.add(resizeDialog_, "ResizeDialog");
        resizeDialog_->load(THEME_CONFIG_FILE);
        resizeDialog_->setSize(dialogSize.x, dialogSize.y);
        resizeDialog_->setPosition(0, 0);
        resizeDialog_->setTitle("Resize");
        resizeDialog_->bindCallback(&GameMenu::closeResizeDialog, this, tgui::ChildWindow::Closed);

        tgui::Grid::Ptr grid(*resizeDialog_);
        grid->setSize(dialogSize.x, dialogSize.y);

        tgui::Label::Ptr countLabel(*grid, "CountLabel");
        countLabel->setText("Living Cells:");
        countLabel->setTextSize(16);
        grid->addWidget(countLabel, 0, 0);

        grid->add(countEdit_, "CountEdit");
        countEdit_->setSize(editSize.x, editSize.y);
        countEdit_->load(THEME_CONFIG_FILE);
        grid->addWidget(countEdit_, 0, 1);

        tgui::Label::Ptr widthLabel(*grid, "WidthLabel");
        widthLabel->setText("Grid width:");
        widthLabel->setTextSize(16);
        grid->addWidget(widthLabel, 1, 0);

        grid->add(widthEdit_, "WidthEdit");
        widthEdit_->setSize(editSize.x, editSize.y);
        widthEdit_->load(THEME_CONFIG_FILE);
        grid->addWidget(widthEdit_, 1, 1);

        tgui::Label::Ptr heightLabel(*grid, "HeightLabel");
        heightLabel->setText("Grid Height:");
        heightLabel->setTextSize(16);
        grid->addWidget(heightLabel, 2, 0);

        grid->add(heightEdit_, "HeightEdit");
        heightEdit_->setSize(editSize.x, editSize.y);
        heightEdit_->load(THEME_CONFIG_FILE);
        grid->addWidget(heightEdit_, 2, 1);

        grid->add(infoLabel_, "InfoLabel");
        infoLabel_->setText("hallo");
        infoLabel_->setTextColor(sf::Color::Red);
        infoLabel_->setTextSize(16);
        grid->addWidget(infoLabel_, 3, 0);

        tgui::Button::Ptr applyButton(*grid, "ApplyButton");
        applyButton->load(THEME_CONFIG_FILE);
        applyButton->setSize(buttonSize.x, buttonSize.y);
        applyButton->setText("Apply");
        applyButton->setTextSize(16);
        grid->addWidget(applyButton, 4, 0);
        applyButton->bindCallback(&GameMenu::resizeApply, this,
                tgui::Button::LeftMouseClicked);

        tgui::Button::Ptr cancelButton(*grid, "CancelButton");
        cancelButton->load(THEME_CONFIG_FILE);
        cancelButton->setSize(buttonSize.x, buttonSize.y);
        cancelButton->setText("Cancel");
        cancelButton->setTextSize(16);
        grid->addWidget(cancelButton, 4, 1);
        cancelButton->bindCallback(&GameMenu::resizeCancel, this,
                tgui::Button::LeftMouseClicked);

        grid->updateWidgets();
        infoLabel_->setText("");
        closeResizeDialog();
    }

    void GameMenu::clearResizeEdits()
    {
        countEdit_->setText("");
        widthEdit_->setText("");
        heightEdit_->setText("");
    }

    void GameMenu::openResizeDialog()
    {
        if(dialogOpen_)
           return;

        clearResizeEdits();
        infoLabel_->setText("");
        float x = gui_.getSize().x / 2 - resizeDialog_->getSize().x / 2;
        float y = gui_.getSize().y / 2 - resizeDialog_->getSize().y / 2;
        resizeDialog_->setPosition(x,y);

        dialogOpen_ = true;
        resizeDialog_->show();
        resizeDialog_->enable();
    }

    void GameMenu::closeResizeDialog()
    {
        resizeDialog_->disable();
        resizeDialog_->hide();
        dialogOpen_ = false;
    }

    void GameMenu::resizeCancel()
    {
        clearResizeEdits();
        closeResizeDialog();
    }

    void GameMenu::resizeApply()
    {
        unsigned int count, width, height;
        bool failedConversion = !(std::istringstream(countEdit_->getText())
                >> count)
                || !(std::istringstream(widthEdit_->getText()) >> width)
                || !(std::istringstream(heightEdit_->getText()) >> height);
        if(failedConversion)
            infoLabel_->setText("only positive numbers");
        else {
            world_.reinit(width,height, count);
            closeResizeDialog();
        }
    }

    void GameMenu::initControlsDialog()
        {
            sf::Vector2f dialogSize(400, 200);
            gui_.add(controlsDialog_, "ResizeDialog");
            controlsDialog_->load(THEME_CONFIG_FILE);
            controlsDialog_->setSize(dialogSize.x, dialogSize.y);
            controlsDialog_->setPosition(0, 0);
            controlsDialog_->setTitle("Controls");
            controlsDialog_->bindCallback(&GameMenu::closeControlsDialog, this, tgui::ChildWindow::Closed);

            tgui::Grid::Ptr grid(*controlsDialog_);
            grid->setSize(dialogSize.x, dialogSize.y);

            tgui::Label::Ptr labelLeftMB(*grid);
            labelLeftMB->load(THEME_CONFIG_FILE);
            labelLeftMB->setText("Left Mouse Button:");
            labelLeftMB->setTextSize(18);
            grid->addWidget(labelLeftMB, 0, 0);

            tgui::Label::Ptr labelLeftMBCtrl(*grid);
            labelLeftMBCtrl->load(THEME_CONFIG_FILE);
            labelLeftMBCtrl->setText("Scroll");
            labelLeftMBCtrl->setTextSize(18);
            grid->addWidget(labelLeftMBCtrl, 0, 1);

            tgui::Label::Ptr labelRightMB(*grid);
            labelRightMB->load(THEME_CONFIG_FILE);
            labelRightMB->setText("Right Mouse Button:");
            labelRightMB->setTextSize(18);
            grid->addWidget(labelRightMB, 1, 0);

            tgui::Label::Ptr labelRightMBCtrl(*grid);
            labelRightMBCtrl->load(THEME_CONFIG_FILE);
            labelRightMBCtrl->setText("Paint Living Cells");
            labelRightMBCtrl->setTextSize(18);
            grid->addWidget(labelRightMBCtrl, 1, 1);

            grid->updateWidgets();
            closeControlsDialog();
        }

        void GameMenu::openControlsDialog()
        {
            if(dialogOpen_)
                return;

            dialogOpen_ = true;
            controlsDialog_->show();
            controlsDialog_->enable();
        }

        void GameMenu::closeControlsDialog()
        {
            controlsDialog_->disable();
            controlsDialog_->hide();
            dialogOpen_ = false;
        }

    void GameMenu::handleEvent(const sf::Event &event)
    {
        if(event.type == event.Resized) {
            tgui::MenuBar::Ptr menu = getMenuBar();
            menu->setSize(event.size.width, menu->getSize().y);
        }
    }

    bool GameMenu::hasOpenDialog() const
    {
        return dialogOpen_;
    }

}

