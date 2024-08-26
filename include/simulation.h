#pragma once
#include "actors.h"
#include "constants.h"
#include "information.h"
#include "instruments.h"
#include "market.h"
#include <vector>
#include <set>

namespace simulation {

    // Simulation class and logic
    class Simulation {
        private:
            constants::config_t config;
            information::NewsStream news_stream;
            std::vector<instruments::Sector> sectors;
            std::vector<information::Emitter> emitters;
            market::Market market;
            std::vector<actors::Actor> actors;
            std::vector<std::shared_ptr<instruments::Stock>> instruments;
            std::vector<std::shared_ptr<instruments::Company>> companies;

        public:
            int tick;

            void init(constants::config_t);
            void simulate_tick();
            void display_current();
            void stop();
    };
}