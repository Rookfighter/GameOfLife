#include <vector>
#include "Cell.hpp"

namespace gol
{
    class Grid
    {
    private:
        std::vector<std::vector<Cell>> grid_;
        
    public:
        Grid(const unsigned int width, const unsigned int height);
        ~Grid();
        
        void setStateOf(const unsigned int x, const unsigned int y, const Cell::State state);
        Cell get(const unsigned int x, const unsigned int y) const;
        
        void resize(const unsigned int width, const unsigned int height);
        void reset();
    };
}
