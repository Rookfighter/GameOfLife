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
    public:
        GridDrawer(Grid &grid);
        ~GridDrawer();

        void draw(sf::RenderTarget& target) const;
    };
}

#endif
