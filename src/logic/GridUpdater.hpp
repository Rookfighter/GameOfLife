#ifndef GOL_GRIDUPDATER_HPP
#define GOL_GRIDUPDATER_HPP

#include <list>
#include "logic/Grid.hpp"

namespace gol
{
    class GridUpdater
    {
    private:
        Grid &grid_;
        std::list<Coordinate> willDie_;
        std::list<Coordinate> willBeBorn_;


        void updateStateChanges();
        void updateCells();
    public:
        GridUpdater(Grid &grid);
        ~GridUpdater();

        void update();
    };

}

#endif
