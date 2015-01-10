#include <cassert>
#include "app/GameLoop.hpp"

#define DEF_INTERVAL (1000000 / 60)

namespace gol
{

    GameLoop::GameLoop(const std::function<void()> &update, const std::function<void()> &redraw)
            : drawInterval_(sf::microseconds(DEF_INTERVAL)), updateInterval_(
                    sf::microseconds(DEF_INTERVAL)), timeAccount_(
                    sf::Time::Zero), lastRun_(sf::Time::Zero), paused_(false), keepRunning_(
                    false),
                    update_(update),
                    redraw_(redraw)
    {
        assert(update_ && redraw_);
    }

    GameLoop::~GameLoop()
    {
    }

    void GameLoop::start()
    {
        keepRunning_ = true;
        run();
    }

    void GameLoop::run()
    {
        sf::Time toSleep;
        sf::Clock clock;
        update_();
        redraw_();
        toSleep = drawInterval_ - clock.getElapsedTime();
        sf::sleep(toSleep);
        lastRun_ = clock.getElapsedTime();
        timeAccount_ += lastRun_;

        while(keepRunning_) {
            clock.restart();
            while(timeAccount_ > updateInterval_ && !paused_) {
                update_();
                timeAccount_ -= updateInterval_;
            }

            redraw_();
            toSleep = drawInterval_ - clock.getElapsedTime();
            sf::sleep(toSleep);
            lastRun_ = clock.getElapsedTime();

            if(!paused_)
                timeAccount_ += lastRun_;
        }
    }

    void GameLoop::stop()
    {
        keepRunning_ = false;
    }

    void GameLoop::pause()
    {
        paused_ = true;
    }

    void GameLoop::resume()
    {
        paused_ = false;
    }

    void GameLoop::setDrawInterval(const sf::Time interval)
    {
        drawInterval_ = interval;
    }

    void GameLoop::setUpdateInterval(const sf::Time interval)
    {
        updateInterval_ = interval;
    }
}
