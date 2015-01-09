#ifndef LOGIC_GRID_HPP
#define LOGIC_GRID_HPP

#include <vector>
#include <list>
#include "logic/Coordinate.hpp"
#include "logic/Cell.hpp"

namespace gol
{

    class Grid
    {
    private:
        std::vector<std::vector<Cell>> map_;
        std::list<Coordinate> livingCells_;
    public:
        Grid();
        Grid(const unsigned int width, const unsigned int height);
        ~Grid();

        void resize(const unsigned int width, const unsigned int height);
        void reset();
        void setStateOf(const unsigned int x, const unsigned y, const Cell::State state);

        Cell::State getStateOf(const unsigned int x, const unsigned y) const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        const std::vector<std::vector<Cell>>& getMap() const;
        const std::list<Coordinate> getLivingCells() const;
    };

}

#endif
