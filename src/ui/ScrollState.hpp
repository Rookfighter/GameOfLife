#ifndef SRC_UI_SCROLLSTATE_HPP_
#define SRC_UI_SCROLLSTATE_HPP_

#include "ui/WindowState.hpp"

namespace gol
{

    class ScrollState: public WindowState
    {
    private:
        sf::Vector2i lastPos_;
    public:
        ScrollState(WindowProperties &properties, const sf::Vector2i &mousePos);
        ~ScrollState();

        WindowState* handleInput(const sf::Event &event);
    };

}

#endif
