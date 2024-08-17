#pragma once

namespace actors
{
    class Actor;
}

#include <map>
#include <string>
#include <vector>
#include "market.h"
#include "instruments.h"

namespace actors
{
    // Base actors
    using portfolio_t = std::map<instruments::Stock, int>;

    class Actor
    {
        int id;
        double risk_adversity;
        int age;
        int execution_pace;
        double cash;
        std::vector<int> active_orders;
        void buy(market::Market &, instruments::Stock &, market::OrderType, int, double price);
        void sell(market::Market &, instruments::Stock &, market::OrderType, int, double price);

    public:
        portfolio_t portfolio;
        Actor(int, double, int, int, double);
    };

}