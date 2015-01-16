#ifndef LOGIC_COORDINATE_HPP
#define LOGIC_COORDINATE_HPP

namespace gol
{

    class Coordinate
    {
    public:
        unsigned int x;
        unsigned int y;

        Coordinate();
        Coordinate(const unsigned px, const unsigned py);
        ~Coordinate();

        void set(const unsigned px, const unsigned py);

        bool operator==(const Coordinate &coordinate) const;

    };

    inline int coordHashCode(const Coordinate &coord)
    {
        return 137 * coord.x + 149 * coord.y;
    }

    inline bool coordIsLess(const Coordinate &coord1, const Coordinate &coord2)
    {
        return coordHashCode(coord1) < coordHashCode(coord2);
    }
}

#endif
