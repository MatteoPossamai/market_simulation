#include "constants.h"
#include "simulation.h"
#include <iostream>

namespace simulation
{

    void Simulation::init(constants::config_t config)
    {
        this->config = config;

        // TODO: initialize all internal private data structures
        this->tick = 0;
    }

    void Simulation::display_current()
    {
        // TODO: full display (how) of the current state of simulation
        std::cout << "Time" << this->tick << std::endl;
    }

    void Simulation::simulate_tick()
    {
        // TODO: implement all the logic that happens in a given tick in time
        this->tick++;
    }

    void Simulation::stop()
    {
        std::cout << std::endl
                  << "Simulation completed" << std::endl;
    }
}