#ifndef LOGIC_WORLD_HPP
#define LOGIC_WORLD_HPP

#include "logic/GridUpdater.hpp"
#include "logic/GridDrawer.hpp"

namespace gol
{

    class World
    {
    private:
        std::list<Coordinate> initialLivingCells_;
        Grid grid_;

        GridUpdater updater_;
        GridDrawer drawer_;
    public:
        World();
        World(const unsigned int width, const unsigned int height);
        ~World();

        void init(unsigned int initLivingCells);
        void resize(const unsigned int width, const unsigned int height);
        void reset();

        const Grid& getGrid() const;

        void update();
        void draw(sf::RenderTarget& target) const;
    };

}

#endif
