#ifndef GOL_GRIDUPDATER_HPP
#define GOL_GRIDUPDATER_HPP

#include <set>
#include <array>
#include "logic/Grid.hpp"

namespace gol
{
    class GridUpdater
    {
    private:
        Grid &grid_;
        std::set<Coordinate, bool (*) (const Coordinate&, const Coordinate&)> willDie_;
        std::set<Coordinate, bool (*) (const Coordinate&, const Coordinate&)> willBeBorn_;

        static const unsigned int NEIGHBOURS = 8;

        void updateStateChanges();
        void updateCells();
        unsigned int getDeadNeighbours(const Coordinate &coordinate, std::array<Coordinate, NEIGHBOURS> &neighbours);
    public:
        GridUpdater(Grid &grid);
        ~GridUpdater();

        void update();
    };

}

#endif
