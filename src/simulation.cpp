#include "actors.h"
#include "instruments.h"
#include "simulation.h"
#include "market.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <map>

namespace simulation
{

    std::string log_string = "[LOG] ";
    void Simulation::init(constants::config_t config)
    {
        std::vector<std::string> sector_names = {"Technology", "Industry", "Food&Beverage", "Travel", "Luxory", "Energy", "Healthcare", "Finance", "Education", "Insurance", "Agriculture"};
        this->config = config;
        this->tick = 0;
        srand((unsigned)time(NULL));
        double max_starting_cash = 10000000;
        this->news_stream = information::NewsStream();

        std::map<std::string, std::string> simulation_config = this->config.at("simulation");

        if (simulation_config.count("max_starting_cash"))
        {
            max_starting_cash = std::stoi(simulation_config.at("max_starting_cash"));
        }

        // Create actors
        int actor_number = std::stoi(simulation_config.at("actors"));
        for (int i = 0; actor_number > i; i++)
        {
            this->actors.push_back(actors::Actor(i, rand() % 100, rand() % 10, rand() % 100000000));
        }
        // Sort so that the fastest exection happens first
        std::sort(this->actors.begin(), this->actors.end());

        // Create sectors
        int sector_number = std::stoi(simulation_config.at("sectors"));
        for (int i = 0; sector_number > i; i++)
        {
            this->sectors.push_back(instruments::Sector(
                sector_names.at(rand() % sector_names.size()) + std::to_string(i)));
        }

        // Create companies
        for (int i = 0; std::stoi(simulation_config.at("instruments")) > i; i++)
        {
            long int stocks = rand() % 1000000;
            long int owned = stocks - (rand() % 10000);
            this->companies.push_back(
                instruments::Company(
                    i, stocks, owned, rand() % 1000000, this->sectors[rand() % this->sectors.size()]));
        }

        // Allocate instruments
        for (int i = 0; std::stoi(simulation_config.at("instruments")) > i; i++)
        {
            long int stocks = rand() % 1000000;
            long int owned = stocks - (rand() % 10000);
            this->instruments.push_back(
                &this->companies.at(i).stock);
        }
        // TODO: random stock distribution to initialize

        // Create emitters
        for (int i = 0; std::stoi(simulation_config.at("emitters")) > i; i++)
        {
            this->emitters.push_back(
                information::Emitter(
                    "Emitter" + std::to_string(i), ((double)rand() / (RAND_MAX)) + 1, information::EmitterType::OFFICIAL_EMITTER));
        }

        // Create markets
        // TODO: register all the stoks in the market's lists
        this->market = market::Market("Stock market");
    }

    void Simulation::display_current()
    {
        std::cout << log_string << "Time: " << this->tick << std::endl << "----------------------------------" << std::endl;


            std::cout << market.name << std::endl;
            for (instruments::Stock *instrument : this->instruments)
            {
                (*instrument).show();
                if (market.buy_orders.count(instrument))
                {
                    std::cout << log_string << "\tTop buy order: " << std::endl
                              << log_string << "\t================" << std::endl;
                    std::cout << log_string << "\t\tPrice:" << market.buy_orders.at(instrument).top()->quantity << std::endl;
                }
                std::cout << std::endl;
                if (market.sell_orders.count(instrument))
                {
                    std::cout << log_string << "\tTop sell order: " << std::endl
                              << log_string <<"\t================" << std::endl;
                    std::cout << log_string << "\t\tPrice:" << market.sell_orders.at(instrument).top()->quantity << std::endl;
                }
            }
        std::cout << "----------------------------------" << std::endl;
    }

    void Simulation::simulate_tick()
    {
        // Emitters that emit news
        for (information::Emitter emitter : this->emitters){
            emitter.emit(this->news_stream, this->tick, &this->companies.at(rand() % this->companies.size()), &this->sectors.at(rand() % this->sectors.size()));
        }

        // Actors trade
        for (actors::Actor actor : this->actors){
            actor.act(this->news_stream, this->companies, this->market);
        }
        this->tick++;
    }

    void Simulation::stop()
    {
        std::cout << std::endl
                  << "Simulation completed" << std::endl;
    }
}