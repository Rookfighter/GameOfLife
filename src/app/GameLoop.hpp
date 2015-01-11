#ifndef GOL_GAMELOOP_HPP
#define GOL_GAMELOOP_HPP

#include <SFML/System.hpp>
#include <functional>

namespace gol
{
    class GameLoop
    {
    private:
        sf::Time drawInterval_;
        sf::Time updateInterval_;
        sf::Time timeAccount_;
        sf::Time lastRun_;


        sf::Time drawIntervalBuff_;
        sf::Time updateIntervalBuff_;
        volatile bool paused_;
        volatile bool keepRunning_;

        std::function<void()> processInput_;
        std::function<void()> update_;
        std::function<void()> redraw_;

        void run();
    public:
        GameLoop(const std::function<void()> &update, const std::function<void()> &redraw, const std::function<void()> &processInput);
        ~GameLoop();

        void start();
        void stop();

        void pause();
        void resume();

        void setDrawInterval(const sf::Time interval);
        void setUpdateInterval(const sf::Time interval);

        const sf::Time& getDrawInterval() const;
        const sf::Time& getUpdateInterval() const;
    };

}

#endif
