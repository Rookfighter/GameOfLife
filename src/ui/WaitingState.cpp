#include "ui/WaitingState.hpp"
#include "ui/ScrollState.hpp"
#include "ui/PaintState.hpp"

namespace gol
{

    WaitingState::WaitingState(WindowProperties &properties)
    :WindowState(properties)
    {

    }

    WaitingState::~WaitingState()
    {
    }

    WindowState* WaitingState::handleInput(const sf::Event& event)
    {
        WindowState *result = nullptr;

        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                result = new ScrollState(properties_, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                result = new PaintState(properties_, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
        }

        return result;
    }

}
