#include "instruments.h"
#include "market.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

namespace instruments
{
    double Stock::get_current_price(const market::Market &market, long int stock, long int owned, long int debt) const
    {
        if ((market.sell_orders.size() == 0 || market.sell_orders.at(self).size()) == 0 && (market.buy_orders.size() == 0 || market.buy_orders.at(self).size() == 0))
        {
            auto cmp = this->company.get();
            const double initial_value = ((stock / owned) - (debt / 100)) * 100;
            std::cout << "Initial value of " << this->ticker << " is : " << initial_value << std::endl;
            return initial_value;
        }
        else if (market.sell_orders.at(self).size() == 0)
        {
            return market.buy_orders.at(self).top().get()->price;
        }
        else if (market.buy_orders.at(self).size() == 0)
        {
            return market.sell_orders.at(self).top().get()->price;
        }
        else
        {
            double top_sell_price = market.sell_orders.at(self).top().get()->price;
            double top_buy_price = market.buy_orders.at(self).top().get()->price;
            return (top_buy_price + top_sell_price) / 2;
        }
    }

    void Stock::show(std::string initial_string)
    {
        std::cout << initial_string << "Ticker: " << this->ticker << std::endl;
    }

    Company::Company(int id_value, long int n_stock_value, long int n_owned_stock_value, long int debt, Sector &sector_value)
        : id(id_value),
          n_stocks(n_stock_value),
          n_owned_stocks(n_owned_stock_value),
          debt(debt),
          sector(sector_value)
    {
        auto stock_p = std::make_shared<Stock>();
        stock_p.get()->self = stock_p;
        this->stock = stock_p;
    }

    int Company::market_cap(const market::Market &market) const
    {
        return n_stocks * (this->stock.get()->get_current_price(market, 0, 0, 0));
    }

    Sector::Sector(std::string name_value) : name(name_value), valuation(rand() % 100) {}

}