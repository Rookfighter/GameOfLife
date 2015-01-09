#include "Cell.hpp"

namespace gol
{
    Cell::Cell()
    :state_(DEAD)
    {
    }
    
    Cell::~Cell
    {
    }
    
    void Cell:setState(const State state)
    {
        state_ = state;
    }
    
    State Cell:getState() const
    {
        return state_;
    }
}
