#include "logic/GridUpdater.hpp"

namespace gol
{
    GridUpdater::GridUpdater(Grid& grid)
            : grid_(grid), willDie_(coordIsLess), willBeBorn_(coordIsLess)
    {
    }

    GridUpdater::~GridUpdater()
    {
    }

    void GridUpdater::update()
    {
        updateStateChanges();
        updateCells();
    }

    void GridUpdater::updateStateChanges()
    {
        willBeBorn_.clear();
        willDie_.clear();
        std::array<Coordinate, NEIGHBOURS> deadNeighbours;
        std::array<Coordinate, NEIGHBOURS> dummyNeighbours;

        for(Coordinate coord : grid_.getLivingCells()) {
            // check if this Cell will die
            unsigned int deadCount = getDeadNeighbours(coord, deadNeighbours);
            unsigned int livingCount = NEIGHBOURS - deadCount;

            if(livingCount < 2 || livingCount > 3)
                willDie_.insert(coord);

            // check for all dead neighbours if they will get alive
            for(unsigned int i = 0; i < deadCount; ++i) {
                unsigned int livingCountTmp = NEIGHBOURS
                        - getDeadNeighbours(deadNeighbours[i], dummyNeighbours);
                if(livingCountTmp == 3)
                    willBeBorn_.insert(deadNeighbours[i]);
            }
        }
    }

    void GridUpdater::updateCells()
    {
        for(Coordinate coord : willDie_)
            grid_.setStateOf(coord.x, coord.y, Cell::State::DEAD);

        for(Coordinate coord : willBeBorn_)
            grid_.setStateOf(coord.x, coord.y, Cell::State::ALIVE);
    }

    unsigned int GridUpdater::getDeadNeighbours(const Coordinate &coordinate,
            std::array<Coordinate, NEIGHBOURS> &neighbours)
    {
        unsigned int result = 0;
        int x, y;

        //check right side
        x = (coordinate.x + 1) % grid_.getWidth();
        y = coordinate.y;
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        y = (coordinate.y + 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        y = (coordinate.y - 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        // check left side
        x = (coordinate.x - 1) % grid_.getWidth();
        y = coordinate.y;
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        y = (coordinate.y + 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        y = (coordinate.y - 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        // check top mid
        x = coordinate.x;
        y = (coordinate.y + 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        // check bot mid
        y = (coordinate.y - 1) % grid_.getHeight();
        if(grid_.getStateOf(x, y) == Cell::State::DEAD) {
            neighbours[result].set(x, y);
            ++result;
        }

        return result;
    }

}
