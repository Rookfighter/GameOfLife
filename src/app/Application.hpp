#ifndef GOL_APPLICATION_HPP
#define GOL_APPLICATION_HPP

#include "ui/GameWindow.hpp"
#include "logic/World.hpp"
#include "app/GameLoop.hpp"

namespace gol
{
    class Application
    {
    private:
        World world_;
        GameLoop gameLoop_;
        GameWindow window_;

        void processInput();
        void update();
    public:
        Application();
        ~Application();

        int run();
    };

}

#endif
