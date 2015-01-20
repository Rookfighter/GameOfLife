#include <cassert>
#include "logic/Grid.hpp"

namespace gol
{

    Grid::Grid()
            :Grid(3, 3)
    {
    }

    Grid::Grid(const unsigned int width, const unsigned int height)
    :width_(width), height_(height), map_(width * height)
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
        for(unsigned int i = 0; i < map_.size(); ++i) {
            map_[i].setState(Cell::State::DEAD);
            map_[i].setLivingNeighbours(0);
        }
    }

    unsigned int Grid::index(const unsigned int x, const unsigned int y) const
    {
        return x + y * width_;
    }

    void Grid::setStateOf(const unsigned int x, const unsigned int y,
            const Cell::State state)
    {
        assert(x < width_ && y < height_);
        std::array<unsigned int, NEIGHBOURS> neighbours;
        getNeighbours(x, y, neighbours);
        unsigned int idx = index(x,y);

        if(map_[idx].getState() == Cell::State::ALIVE
                && state != Cell::State::ALIVE) {
            // cell died
            for(unsigned int neighbour: neighbours)
                map_[neighbour].decLivingNeighbours();
        } else if(map_[idx].getState() != Cell::State::ALIVE
                && state == Cell::State::ALIVE) {
            // cell was born
            for(unsigned int neighbour: neighbours)
                map_[neighbour].incLivingNeighbours();
        }

        map_[idx].setState(state);
    }

    void Grid::getNeighbours(const unsigned int x, const unsigned int y, std::array<unsigned int, NEIGHBOURS> &result)
    {
        unsigned int currx, curry;

        // check right column
        currx = (x + 1) % width_;
        curry = y;
        result[0] = index(currx, curry);
        curry = (y + 1) % height_;
        result[1] = index(currx, curry);
        curry = (y - 1) % height_;
        result[2] = index(currx, curry);

        // check mid column
        currx = x;
        curry = (y + 1) % height_;
        result[3] = index(currx, curry);
        curry = (y - 1) % height_;
        result[4] = index(currx, curry);

        // check left column
        currx = (x - 1) % width_;
        curry = y;
        result[5] = index(currx, curry);
        curry = (y + 1) % height_;
        result[6] = index(currx, curry);
        curry = (y - 1) % height_;
        result[7] = index(currx, curry);
    }

    Cell::State Grid::getStateOf(const unsigned int x, const unsigned int y) const
    {
        assert(x < width_ && y < height_);

        return map_[index(x,y)].getState();
    }

    unsigned int Grid::getLivingNeighboursOf(const unsigned int x, const unsigned int y) const
    {
        assert(x < width_ && y < height_);

        return map_[index(x,y)].getLivingNeighbours();
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

}
