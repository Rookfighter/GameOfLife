#ifndef UI_WINDOWPROPERTIES_HPP
#define UI_WINDOWPROPERTIES_HPP

#include <SFML/Graphics.hpp>
#include "logic/World.hpp"

namespace gol
{

    class WindowProperties
    {
    private:
        World &world_;
        sf::RenderWindow &window_;
        sf::View gameView_;
        sf::View guiView_;
    public:

        WindowProperties(World &world, sf::RenderWindow &window)
                : world_(world), window_(window)
        {
        }
        ~WindowProperties()
        {
        }

        void setGameView(const sf::View &view)
        {
            gameView_ = view;
        }

        sf::View& getGameView()
        {
            return gameView_;
        }

        void setGuiView(const sf::View &view)
        {
            guiView_ = view;
        }

        sf::View& getGuiView()
        {
            return guiView_;
        }

        World& getWorld()
        {
            return world_;
        }

        sf::RenderWindow& getWindow()
        {
            return window_;
        }
    };

}

#endif
