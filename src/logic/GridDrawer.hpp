#ifndef GOL_GRIDDRAWER_HPP
#define GOL_GRIDDRAWER_HPP

#include <SFML/Graphics.hpp>
#include "logic/Grid.hpp"

namespace gol
{

    class GridDrawer
    {
    private:
        Grid &grid_;
        unsigned int width_;
        unsigned int height_;
        sf::VertexArray vertexArray_;
        sf::VertexArray background_;
        sf::Vector2f cellSize_;

        void resize();
        unsigned int quadIndex(const unsigned int x, const unsigned int y) const;
    public:
        GridDrawer(Grid &grid);
        ~GridDrawer();

        void draw(sf::RenderTarget& target);
    };
}

#endif
