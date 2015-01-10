#include <easylogging++.h>
#include "app/Application.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
    el::Configurations conf("config/easylog.conf");
    el::Loggers::reconfigureAllLoggers(conf);
    gol::Application app;
    return app.run();
}
