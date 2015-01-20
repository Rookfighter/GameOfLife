#include "logic/GridUpdater.hpp"

namespace gol
{
    GridUpdater::GridUpdater(Grid& grid)
            : grid_(grid), willDie_(), willBeBorn_()
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
        unsigned int livingNeighbours;

        for(unsigned int x = 0; x < grid_.getWidth(); ++x) {
            for(unsigned int y = 0; y < grid_.getHeight(); ++y) {
                livingNeighbours = grid_.getLivingCellsOf(x,y);

                if(grid_.getStateOf(x,y) == Cell::State::ALIVE) {
                    // cell is alive
                    if(livingNeighbours < 2 || livingNeighbours > 3) {
                        willDie_.push_back(Coordinate(x,y));
                    }
                } else {
                    // cell is dead
                    if(livingNeighbours == 3) {
                        willBeBorn_.push_back(Coordinate(x,y));
                    }
                }
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
}
