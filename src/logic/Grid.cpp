#include <cassert>
#include "Grid.hpp"

namespace gol
{
    Grid::Grid(const unsigned int width, const unsigned int height)
    {
        resize(width, height);
    }
    
    Grid::~Grid()
    {
    
    }
    
    void Grid::setStateOf(const unsigned int x, const unsigned int y, const Cell::State state)
    {
    
    }
    
    Cell Grid::get(const unsigned int x, const unsigned int y) const
    {
    
    }
    
    void resize(const unsigned int width, const unsigned int height)
    {
        grid_.resize(width);
        
        for(unsigned int i = 0; i <
    }
    
    void reset()
    {
    
    }
}
