#ifndef LOGIC_GRID_HPP
#define LOGIC_GRID_HPP

#include <vector>
#include <array>
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
        static const unsigned int NEIGHBOURS = 8;

        unsigned int index(const unsigned int x, const unsigned int y) const;
        void getNeighbours(const unsigned int x, const unsigned int y, std::array<unsigned int, NEIGHBOURS> &result);
    public:
        Grid();
        Grid(const unsigned int width, const unsigned int height);
        ~Grid();

        void resize(const unsigned int width, const unsigned int height);
        void reset();
        void setStateOf(const unsigned int x, const unsigned int y, const Cell::State state);

        Cell::State getStateOf(const unsigned int x, const unsigned int y) const;
        unsigned int getLivingNeighboursOf(const unsigned int x, const unsigned int y) const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        unsigned int getCount() const;
        float getCellWidth() const;
        float getCellHeight() const;
        const std::vector<Cell>& getMap() const;

    };

}

#endif
