#ifndef LOGIC_CELL_HPP
#define LOGIC_CELL_HPP

namespace gol
{
    class Cell
    {
    public:
        enum State {ALIVE, DEAD};
    private:
        State state_;
    public:
        Cell();
        ~Cell();
        
        void setState(const State state);
        State getState() const;
    };
}

#endif
