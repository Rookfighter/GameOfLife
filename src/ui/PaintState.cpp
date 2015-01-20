#include <easylogging++.h>
#include "ui/PaintState.hpp"
#include "ui/WaitingState.hpp"

namespace gol
{

    PaintState::PaintState(WindowProperties &properties,
            const sf::Vector2i &mousePos)
            : WindowState(properties), lastPos_(mousePos)
    {
        paintCell();
    }

    PaintState::~PaintState()
    {
    }

    WindowState* PaintState::handleInput(const sf::Event& event)
    {
        WindowState *result = nullptr;
        if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Right)
                result = new WaitingState(properties_);
        } else if(event.type == sf::Event::MouseMoved) {
            lastPos_.x = event.mouseMove.x;
            lastPos_.y = event.mouseMove.y;
            paintCell();
        }

        return result;
    }

    void PaintState::paintCell()
    {
        float gridWidth = properties_.getWorld().getGrid().getWidth()
                * properties_.getWorld().getGrid().getCellWidth();
        float gridHeight = properties_.getWorld().getGrid().getHeight()
                * properties_.getWorld().getGrid().getCellHeight();
        sf::Vector2f posToPaint = properties_.getWindow().mapPixelToCoords(
                lastPos_, properties_.getGameView());
        if(posToPaint.x < 0 || posToPaint.x > gridWidth || posToPaint.y < 0
                || posToPaint.y > gridHeight)
            return;


        unsigned int cellX = (unsigned int) (posToPaint.x / properties_.getWorld().getGrid().getCellWidth());
        unsigned int cellY = (unsigned int) (posToPaint.y / properties_.getWorld().getGrid().getCellHeight());
        properties_.getWorld().birthCell(cellX, cellY);
    }

}
