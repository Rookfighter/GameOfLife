#include <cassert>
#include "app/GameLoop.hpp"

#define DEF_INTERVAL (1000000 / 60)

namespace gol
{

    GameLoop::GameLoop(const std::function<void()> &update,
            const std::function<void()> &redraw,
            const std::function<void()> &processInput)
            : drawInterval_(sf::microseconds(DEF_INTERVAL)), updateInterval_(
                    sf::microseconds(DEF_INTERVAL)), timeAccount_(
                    sf::Time::Zero), lastRun_(sf::Time::Zero), drawIntervalBuff_(
                    drawInterval_), updateIntervalBuff_(updateInterval_), paused_(
                    false), keepRunning_(false), processInput_(processInput), update_(
                    update), redraw_(redraw)

    {
        assert(update_ && redraw_ && processInput_);
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
        sf::Time toSleep, elapsed;
        sf::Clock clock;
        update_();
        redraw_();
        elapsed = clock.getElapsedTime();
        if(drawInterval_ > elapsed) {
            toSleep = drawInterval_ - clock.getElapsedTime();
            sf::sleep(toSleep);
        }
        lastRun_ = clock.getElapsedTime();
        timeAccount_ += lastRun_;

        while(keepRunning_) {
            clock.restart();
            // process input
            processInput_();

            // update game as long as time account is full
            while(timeAccount_ > updateInterval_ && !paused_) {
                update_();
                timeAccount_ -= updateInterval_;
            }

            // redraw in window
            redraw_();

            // sleep if we were faster than redraw interval
            elapsed = clock.getElapsedTime();
            if(drawInterval_ > elapsed) {
                toSleep = drawInterval_ - clock.getElapsedTime();
                sf::sleep(toSleep);
            }
            lastRun_ = clock.getElapsedTime();

            if(paused_)
                timeAccount_ = sf::Time::Zero;
            else
                timeAccount_ += lastRun_;

            if(drawInterval_ != drawIntervalBuff_)
                drawInterval_ = drawIntervalBuff_;
            if(updateInterval_ != updateIntervalBuff_)
                updateInterval_ = updateIntervalBuff_;
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
        drawIntervalBuff_ = interval;
    }

    void GameLoop::setUpdateInterval(const sf::Time interval)
    {
        updateIntervalBuff_ = interval;
    }

    const sf::Time& GameLoop::getDrawInterval() const
    {
        return drawInterval_;
    }

    const sf::Time& GameLoop::getUpdateInterval() const
    {
        return updateInterval_;
    }
}
