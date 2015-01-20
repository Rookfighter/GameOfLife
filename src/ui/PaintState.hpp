#ifndef UI_PAINTSTATE_HPP
#define UI_PAINTSTATE_HPP

#include "ui/WindowState.hpp"

namespace gol
{

    class PaintState: public WindowState
    {
    private:
        sf::Vector2i lastPos_;

        void paintCell();
    public:
        PaintState(WindowProperties &properties, const sf::Vector2i &mousePos);
        ~PaintState();

        WindowState* handleInput(const sf::Event &event);
    };

}

#endif
