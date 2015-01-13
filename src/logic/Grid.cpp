#include <cassert>
#include "logic/Grid.hpp"

namespace gol
{

    Grid::Grid()
            :Grid(3, 3)
    {
    }

    Grid::Grid(const unsigned int width, const unsigned int height)
    {
        resize(width, height);
    }

    Grid::~Grid()
    {
    }

    void Grid::resize(const unsigned int width, const unsigned int height)
    {
        assert(width > 0 && height > 0);

        map_.resize(width);
        for(unsigned int x = 0; x < width; ++x)
            map_[x].resize(height);

        reset();
    }

    void Grid::reset()
    {
        for(unsigned int x = 0; x < map_.size(); ++x)
            for(unsigned int y = 0; y < map_[x].size(); ++y)
                map_[x][y].setState(Cell::State::DEAD);

        livingCells_.clear();
    }

    void Grid::setStateOf(const unsigned int x, const unsigned y,
            const Cell::State state)
    {
        assert(x < getWidth() && y < getHeight());

        if(map_[x][y].getState() == Cell::State::ALIVE
                && state != Cell::State::ALIVE) {
            // remove cell from the living list
            livingCells_.remove(Coordinate(x, y));
        } else if(map_[x][y].getState() != Cell::State::ALIVE
                && state == Cell::State::ALIVE) {
            // add cell to living list
            livingCells_.push_back(Coordinate(x, y));
        }

        map_[x][y].setState(state);
    }

    Cell::State Grid::getStateOf(const unsigned int x, const unsigned y) const
    {
        assert(x < getWidth() && y < getHeight());

        return map_[x][y].getState();
    }

    unsigned int Grid::getWidth() const
    {
        return map_.size();
    }

    unsigned int Grid::getHeight() const
    {
        return map_[0].size();
    }

    const std::vector<std::vector<Cell> >& Grid::getMap() const
    {
        return map_;
    }

    const std::list<Coordinate> Grid::getLivingCells() const
    {
        return livingCells_;
    }

}
