#ifndef GOL_APPLICATION_HPP
#define GOL_APPLICATION_HPP

#include "logic/World.hpp"
#include "app/GameLoop.hpp"

namespace gol
{
    class Application
    {
    private:
        World world_;
        GameLoop gameLoop_;
        sf::RenderWindow window_;

        void update();
        void redraw();
    public:
        Application();
        ~Application();

        int run();
    };

}

#endif
