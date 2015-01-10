#ifndef GOL_GRIDUPDATER_HPP
#define GOL_GRIDUPDATER_HPP

#include "logic/Grid.hpp"

namespace gol
{
    class GridUpdater
    {
    private:
        Grid &grid_;
        std::list<Coordinate> willDie_;
        std::list<Coordinate> willBeBorn_;

        void getDeadCellsWithLivingNeighbours();
        unsigned int getLivingNeighbourCount(const Coordinate& coordinate);
    public:
        GridUpdater(Grid &grid);
        ~GridUpdater();

        void update();
    };

}

#endif
