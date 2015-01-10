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
}

#endif
