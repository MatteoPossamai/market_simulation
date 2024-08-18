#include "parser.h"
#include "simulation.h"
#include <string>

int main()
{
    // Simulation settings
    const std::string filename = "./config/example1.toml";
    auto config_map = parser::parseTOML(filename);
    const int SIMULATION_TICK_DURATION = 2;

    // Simulation creation
    simulation::Simulation simulation;
    simulation.init(config_map);

    // Run the simulaiton
    simulation.display_current();
    while (simulation.tick < SIMULATION_TICK_DURATION)
    {
        simulation.simulate_tick();
        simulation.display_current();
    }

    simulation.stop();
    return 0;
}