#include <logic/Coordinate.hpp>

namespace gol
{

    Coordinate::Coordinate()
            : x(0), y(0)
    {
    }

    Coordinate::Coordinate(const unsigned px, const unsigned py)
            : x(px), y(py)
    {
    }

    Coordinate::~Coordinate()
    {
    }

    void Coordinate::set(const unsigned px, const unsigned py)
    {
        x = px;
        y = py;
    }

    bool Coordinate::operator==(const Coordinate &coordinate) const
    {
        return x == coordinate.x && y == coordinate.y;
    }
}
