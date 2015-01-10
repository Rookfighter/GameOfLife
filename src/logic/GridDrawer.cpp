#include <logic/GridDrawer.hpp>

namespace gol
{

    GridDrawer::GridDrawer(Grid &grid)
    :grid_(grid)
    {
    }

    GridDrawer::~GridDrawer()
    {
    }

    void GridDrawer::draw(sf::RenderTarget& target) const
    {
        sf::VertexArray vertexArray(sf::Quads, grid_.getWidth() * grid_.getHeight() * 4);
        sf::Vector2f topLeft(0,0);
        sf::Vector2f cellSize(target.getView().getSize());
        cellSize.x /= (float) grid_.getWidth();
        cellSize.y /= (float) grid_.getHeight();

        for(unsigned x = 0; x < grid_.getWidth(); ++x) {
            topLeft.x = ((float)(x)) * cellSize.x; // target.getView().getCenter().x -
            for(unsigned y = 0; y < grid_.getHeight(); ++y) {
                topLeft.y = ((float)(y)) * cellSize.y; // target.getView().getCenter().y -

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &vertexArray[(x + y * grid_.getWidth()) * 4];

                // define its 4 corners
                quad[0].position = topLeft;
                quad[1].position = sf::Vector2f(topLeft.x + cellSize.x, topLeft.y);
                quad[2].position = sf::Vector2f(topLeft.x + cellSize.x, topLeft.y - cellSize.y);
                quad[3].position = sf::Vector2f(topLeft.x, topLeft.y - cellSize.y);

                sf::Color color;
                if(grid_.getStateOf(x,y) == Cell::State::DEAD)
                    color = sf::Color::Black;
                else
                    color = sf::Color::Red;

                quad[0].color = color;
                quad[1].color = color;
                quad[2].color = color;
                quad[3].color = color;
            }
        }

        target.draw(vertexArray);
    }

}
