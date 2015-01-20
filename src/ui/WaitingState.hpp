#ifndef UI_WAITINGSTATE_HPP
#define UI_WAITINGSTATE_HPP

#include "ui/WindowState.hpp"

namespace gol
{

    class WaitingState: public WindowState
    {
    public:
        WaitingState(WindowProperties &properties);
        ~WaitingState();

        WindowState* handleInput(const sf::Event &event);
    };

}

#endif
