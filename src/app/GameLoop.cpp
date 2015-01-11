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
                    sf::Time::Zero), lastRun_(sf::Time::Zero), paused_(
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
            toSleep = drawInterval_ - elapsed;
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
                toSleep = drawInterval_ - elapsed;
                sf::sleep(toSleep);
            }
            lastRun_ = clock.getElapsedTime();

            if(paused_)
                timeAccount_ = sf::Time::Zero;
            else
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

    const sf::Time& GameLoop::getDrawInterval() const
    {
        return drawInterval_;
    }

    const sf::Time& GameLoop::getUpdateInterval() const
    {
        return updateInterval_;
    }

    const sf::Time& GameLoop::getLastDuration() const
    {
        return lastRun_;
    }

    float GameLoop::getDrawFPS() const
    {
        return toFPS(drawInterval_);
    }

    float GameLoop::getUpdateFPS() const
    {
        return toFPS(updateInterval_);
    }

    float GameLoop::getFPS() const
    {
        return toFPS(lastRun_);
    }

    float GameLoop::toFPS(const sf::Time &time) const
    {
        return 1000000.0f / ((float) time.asMicroseconds());
    }
}
