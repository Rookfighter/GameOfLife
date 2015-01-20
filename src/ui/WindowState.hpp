#ifndef SRC_UI_WINDOWSTATE_HPP_
#define SRC_UI_WINDOWSTATE_HPP_

#include "ui/WindowProperties.hpp"

namespace gol
{
    class WindowState
    {
    protected:
        WindowProperties &properties_;
    public:
        WindowState(WindowProperties &properties)
                : properties_(properties)
        {
        }
        virtual ~WindowState()
        {
        }

        virtual WindowState* handleInput(const sf::Event &event) = 0;
    };

}

#endif
