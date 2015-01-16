#include <cassert>
#include "logic/Grid.hpp"

namespace gol
{

    Grid::Grid()
            :Grid(3, 3)
    {
    }

    Grid::Grid(const unsigned int width, const unsigned int height)
    :width_(width), height_(height), map_(width * height), livingCells_(coordIsLess)
    {
        assert(width > 0 && height > 0);
        reset();
    }

    Grid::~Grid()
    {
    }

    void Grid::resize(const unsigned int width, const unsigned int height)
    {
        assert(width > 0 && height > 0);

        width_ = width;
        height_ = height;

        map_.resize(width_ * height_);
        reset();
    }

    void Grid::reset()
    {
        for(unsigned int i = 0; i < map_.size(); ++i)
            map_[i].setState(Cell::State::DEAD);
        livingCells_.clear();
    }

    unsigned int Grid::index(const unsigned int x, const unsigned int y) const
    {
        return x + y * width_;
    }

    void Grid::setStateOf(const unsigned int x, const unsigned int y,
            const Cell::State state)
    {
        assert(x < width_ && y < height_);

        unsigned int idx = index(x,y);

        if(map_[idx].getState() == Cell::State::ALIVE
                && state != Cell::State::ALIVE) {
            // remove cell from the living list
            livingCells_.erase(Coordinate(x, y));
        } else if(map_[idx].getState() != Cell::State::ALIVE
                && state == Cell::State::ALIVE) {
            // add cell to living list
            livingCells_.insert(Coordinate(x, y));
        }

        map_[idx].setState(state);
    }

    Cell::State Grid::getStateOf(const unsigned int x, const unsigned int y) const
    {
        assert(x < width_ && y < height_);

        return map_[index(x,y)].getState();
    }

    unsigned int Grid::getWidth() const
    {
        return width_;
    }

    unsigned int Grid::getHeight() const
    {
        return height_;
    }

    unsigned int Grid::getCount() const
    {
        return map_.size();
    }

    const std::vector<Cell>& Grid::getMap() const
    {
        return map_;
    }

    const std::set<Coordinate, bool (*) (const Coordinate&, const Coordinate&)>& Grid::getLivingCells() const
    {
        return livingCells_;
    }

}
