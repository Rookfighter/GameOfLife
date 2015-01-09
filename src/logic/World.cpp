#include "logic/World.hpp"
#include "utils/Random.hpp"

namespace gol
{

    World::World()
    :grid_()
    {
    }

    World::World(const unsigned int width, const unsigned int height)
    :grid_(width, height)
    {
    }

    World::~World()
    {
    }

    void World::init(unsigned int initLivingCells)
    {
        grid_.reset();

        for(unsigned int i = 0; i < initLivingCells; ++i) {
            unsigned int x = Random::nextInt(grid_.getWidth());
            unsigned int y = Random::nextInt(grid_.getHeight());

            //TODO add timeout
            while(grid_.getStateOf(x,y) == Cell::State::ALIVE) {
                x = Random::nextInt(grid_.getWidth());
                y = Random::nextInt(grid_.getHeight());
            }

            grid_.setStateOf(x, y, Cell::State::ALIVE);
        }

        initialLivingCells_ = grid_.getLivingCells();
    }

    void World::resize(const unsigned int width, const unsigned int height)
    {
        grid_.resize(width, height);
        reset();
    }

    void World::reset()
    {
        grid_.reset();

        for(Coordinate coord : initialLivingCells_) {
            grid_.setStateOf(coord.x, coord.y, Cell::State::ALIVE);
        }
    }

    const Grid& World::getGrid() const
    {
        return grid_;
    }

    void World::update()
    {
    }

    void World::render()
    {
    }

}
