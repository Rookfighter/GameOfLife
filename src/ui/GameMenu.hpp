#ifndef SRC_UI_GAMEMENU_HPP_
#define SRC_UI_GAMEMENU_HPP_

#include <TGUI/TGUI.hpp>
#include "logic/World.hpp"
#include "app/GameLoop.hpp"

namespace gol
{

    class GameMenu
    {
    private:
        World &world_;
        GameLoop &gameLoop_;
        tgui::Gui &gui_;

        tgui::ChildWindow::Ptr resizeDialog_;
        tgui::Label::Ptr infoLabel_;
        tgui::EditBox::Ptr countEdit_;
        tgui::EditBox::Ptr widthEdit_;
        tgui::EditBox::Ptr heightEdit_;

        tgui::ChildWindow::Ptr controlsDialog_;

        bool dialogOpen_;

        void menuItemClicked(const tgui::Callback &callback);

        void initResizeDialog();
        void clearResizeEdits();
        void openResizeDialog();
        void closeResizeDialog();
        void resizeCancel();
        void resizeApply();

        void initControlsDialog();
        void openControlsDialog();
        void closeControlsDialog();
    public:
        GameMenu(World &world, GameLoop &gameLoop, tgui::Gui &gui);
        ~GameMenu();

        tgui::MenuBar::Ptr getMenuBar();

        void init();
        void handleEvent(const sf::Event &event);

        bool hasOpenDialog() const;
    };

}

#endif
