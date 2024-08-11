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
            std::set<instruments::Sector> sectors;
            std::vector<information::Emitter> emitters;
            std::vector<market::Market> markets;
            std::vector<actors::Actor> actors;

        public:
            int tick;

            void init(constants::config_t);
            void simulate_tick();
            void display_current();
            void stop();
    };
}