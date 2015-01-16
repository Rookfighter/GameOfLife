#ifndef LOGIC_GRID_HPP
#define LOGIC_GRID_HPP

#include <vector>
#include <set>
#include "logic/Coordinate.hpp"
#include "logic/Cell.hpp"

namespace gol
{

    class Grid
    {
    private:
        unsigned int width_;
        unsigned int height_;
        std::vector<Cell> map_;
        std::set<Coordinate, bool (*) (const Coordinate&, const Coordinate&)> livingCells_;

        unsigned int index(const unsigned int x, const unsigned int y) const;
    public:
        Grid();
        Grid(const unsigned int width, const unsigned int height);
        ~Grid();

        void resize(const unsigned int width, const unsigned int height);
        void reset();
        void setStateOf(const unsigned int x, const unsigned int y, const Cell::State state);

        Cell::State getStateOf(const unsigned int x, const unsigned int y) const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        unsigned int getCount() const;
        const std::vector<Cell>& getMap() const;
        const std::set<Coordinate, bool (*) (const Coordinate&, const Coordinate&)>& getLivingCells() const;
    };

}

#endif
