#include "logic/Cell.hpp"

namespace gol
{
    Cell::Cell()
    :state_(DEAD)
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

}
