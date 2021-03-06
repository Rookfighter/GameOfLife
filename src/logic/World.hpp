#ifndef LOGIC_WORLD_HPP
#define LOGIC_WORLD_HPP

#include "logic/GridUpdater.hpp"
#include "logic/GridDrawer.hpp"

namespace gol
{

    class World
    {
    private:
        std::vector<Coordinate> initialLivingCells_;
        Grid grid_;

        GridUpdater updater_;
        GridDrawer drawer_;

        void populate(const unsigned int initLivingCells);
    public:
        World();
        World(const unsigned int width, const unsigned int height);
        ~World();

        void repopulate(const unsigned int initLivingCells);
        void reinit(const unsigned int width, const unsigned int height, const unsigned int initLivingCells);
        void reset();
        void birthCell(const unsigned int x, const unsigned int y);

        const Grid& getGrid() const;

        void update();
        void draw(sf::RenderTarget& target);
    };

}

#endif
