#include <cassert>
#include "logic/Cell.hpp"

namespace gol
{
    Cell::Cell()
    :state_(DEAD), livingNeighbours_(0)
    {
    }
    
    Cell::~Cell()
    {
    }
    
    void Cell::setState(const State state)
    {
        state_ = state;
    }
    
    Cell::State Cell::getState() const
    {
        return state_;
    }

    void Cell::setLivingNeighbours(const unsigned int neighbours)
    {
        livingNeighbours_ = neighbours;
    }

    void gol::Cell::incLivingNeighbours()
    {
        ++livingNeighbours_;
    }

    void gol::Cell::decLivingNeighbours()
    {
        assert(livingNeighbours_ > 0);
        --livingNeighbours_;
    }

    unsigned int gol::Cell::getLivingNeighbours() const
    {
        return livingNeighbours_;
    }

}
