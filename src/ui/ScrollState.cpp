#include "ui/ScrollState.hpp"
#include "ui/WaitingState.hpp"

namespace gol
{

    ScrollState::ScrollState(WindowProperties &properties, const sf::Vector2i &mousePos)
    : WindowState(properties), lastPos_(mousePos)
    {

    }

    ScrollState::~ScrollState()
    {
    }

    WindowState* ScrollState::handleInput(const sf::Event& event)
    {
        WindowState *result = nullptr;

        if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Left)
                result = new WaitingState(properties_);
        } else if(event.type == sf::Event::MouseMoved) {
            sf::Vector2f last = properties_.getWindow().mapPixelToCoords(lastPos_,
                    properties_.getGameView());
            sf::Vector2f curr = properties_.getWindow().mapPixelToCoords(
                    sf::Vector2i(event.mouseMove.x, event.mouseMove.y),
                    properties_.getGameView());
            sf::Vector2f diff = last - curr;

            properties_.getGameView().move(diff);
            lastPos_.x = event.mouseMove.x;
            lastPos_.y = event.mouseMove.y;
        }

        return result;
    }

}
