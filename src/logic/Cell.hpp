namespace gol
{
    class Cell
    {
    private:
        State state_;
    
    public:
        enum State = {ALIVE, DEAD};
        
        Cell();
        ~Cell();
        
        void setState(const State state);
        State getState() const;
    };
}
