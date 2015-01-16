#include <logic/GridDrawer.hpp>

namespace gol
{

    GridDrawer::GridDrawer(Grid &grid)
            : grid_(grid), width_(grid_.getWidth()), height_(grid_.getHeight()), vertexArray_(
                    sf::Quads, grid_.getCount() * 4), background_(sf::Quads, 4), cellSize_(
                    2, 2)
    {
        for(unsigned int i = 0; i < background_.getVertexCount(); ++i)
            background_[i].color = sf::Color::White;
        resize();
    }

    GridDrawer::~GridDrawer()
    {
    }

    void GridDrawer::resize()
    {
        width_ = grid_.getWidth();
        height_ = grid_.getHeight();
        vertexArray_.resize(grid_.getCount() * 4);

        background_[0].position = sf::Vector2f(-cellSize_.x, -cellSize_.y);
        background_[1].position = sf::Vector2f(
                width_ * cellSize_.x + cellSize_.x, -cellSize_.y);
        background_[2].position = sf::Vector2f(
                width_ * cellSize_.x + cellSize_.x,
                height_ * cellSize_.y + cellSize_.y);
        background_[3].position = sf::Vector2f(-cellSize_.x,
                height_ * cellSize_.y + cellSize_.y);

        sf::Vector2f topLeft(0, 0);

        for(unsigned x = 0; x < grid_.getWidth(); ++x) {
            topLeft.x = ((float) (x)) * cellSize_.x;
            for(unsigned y = 0; y < grid_.getHeight(); ++y) {
                topLeft.y = ((float) (y)) * cellSize_.y;

                unsigned int idx = quadIndex(x, y);

                // define its 4 corners
                vertexArray_[idx].position = topLeft;
                vertexArray_[idx + 1].position = sf::Vector2f(
                        topLeft.x + cellSize_.x, topLeft.y);
                vertexArray_[idx + 2].position = sf::Vector2f(
                        topLeft.x + cellSize_.x, topLeft.y + cellSize_.y);
                vertexArray_[idx + 3].position = sf::Vector2f(topLeft.x,
                        topLeft.y + cellSize_.y);
            }
        }
    }

    unsigned int GridDrawer::quadIndex(const unsigned int x,
            const unsigned int y) const
    {
        return (x + y * width_) * 4;
    }

    void GridDrawer::draw(sf::RenderTarget& target)
    {
        if(width_ != grid_.getWidth() || height_ != grid_.getHeight())
            resize();

        for(unsigned x = 0; x < grid_.getWidth(); ++x) {
            for(unsigned y = 0; y < grid_.getHeight(); ++y) {
                sf::Color color;
                if(grid_.getStateOf(x, y) == Cell::State::DEAD)
                    color = sf::Color::Black;
                else
                    color = sf::Color::Red;

                unsigned int idx = quadIndex(x, y);

                vertexArray_[idx].color = color;
                vertexArray_[idx + 1].color = color;
                vertexArray_[idx + 2].color = color;
                vertexArray_[idx + 3].color = color;
            }
        }

        target.draw(background_);
        target.draw(vertexArray_);
    }

}
