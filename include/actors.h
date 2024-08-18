#pragma once

namespace actors
{
    class Actor;
}

#include <map>
#include <string>
#include <vector>
#include <assert.h>
#include "market.h"
#include "instruments.h"
#include "information.h"

namespace actors
{
    // Base actors
    using portfolio_t = std::map<std::shared_ptr<instruments::Stock>, int>;

    class Actor
    {
        int id;
        double risk_adversity;
        int execution_pace;
        std::vector<int> active_orders;
        void buy(market::Market &, std::shared_ptr<instruments::Stock>, market::OrderType, int, double price);
        void sell(market::Market &, std::shared_ptr<instruments::Stock>, market::OrderType, int, double price);
        double inspect(const instruments::Company &, const information::NewsStream &);
        double cash;
        double inspect(const instruments::Sector &, const information::NewsStream &);

    public:
        double get_cash() {return this->cash;};
        void set_cash(double value) {
            assert(value > 0);
            this->cash = value;
        }
        bool operator=(const Actor &other) const
        {
            return this->execution_pace == other.execution_pace;
        }
        bool operator<(const Actor &other) const
        {
            return this->execution_pace < other.execution_pace;
        }
        bool operator>(const Actor &other) const
        {
            return this->execution_pace > other.execution_pace;
        }

        portfolio_t portfolio;
        Actor(int, double, int, double);
        void act(const information::NewsStream &, std::vector<instruments::Company> &, market::Market &);
    };

}