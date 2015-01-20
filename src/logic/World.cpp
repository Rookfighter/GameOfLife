#include <cassert>
#include "logic/World.hpp"
#include "utils/Random.hpp"

namespace gol
{

    World::World()
            : grid_(), updater_(grid_), drawer_(grid_)
    {
    }

    World::World(const unsigned int width, const unsigned int height)
            : grid_(width, height), updater_(grid_), drawer_(grid_)
    {
    }

    World::~World()
    {
    }

    void World::populate(const unsigned int initLivingCells)
    {
        assert(initLivingCells <= grid_.getCount());
        initialLivingCells_.resize(initLivingCells);

        for(unsigned int i = 0; i < initLivingCells; ++i) {
            unsigned int x = Random::nextInt(grid_.getWidth());
            unsigned int y = Random::nextInt(grid_.getHeight());

            //TODO add timeout
            while(grid_.getStateOf(x, y) == Cell::State::ALIVE) {
                x = Random::nextInt(grid_.getWidth());
                y = Random::nextInt(grid_.getHeight());
            }

            grid_.setStateOf(x, y, Cell::State::ALIVE);
            initialLivingCells_[i] = Coordinate(x,y);
        }
    }

    void World::repopulate(const unsigned int initLivingCells)
    {
        grid_.reset();
        populate(initLivingCells);
    }

    void World::reinit(const unsigned int width, const unsigned int height,
            const unsigned int initLivingCells)
    {
        grid_.resize(width, height);
        populate(initLivingCells);
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
        updater_.update();
    }

    void World::draw(sf::RenderTarget& target)
    {
        drawer_.draw(target);
    }

}
