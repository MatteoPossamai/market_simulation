#include "instruments.h"
#include "market.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

namespace instruments
{
    Stock::Stock(std::string ticker_name, const Company &company)
        : ticker(ticker_name), company(company) {}

    double Stock::get_current_price(const market::Market &market)
    {
        double top_sell_price = market.sell_orders.at(this).top().get()->price;
        double top_buy_price = market.buy_orders.at(this).top().get()->price;
        return (top_buy_price + top_sell_price) / 2; // TODO: understand if good metric or should put the price at which it sells
    }

    void Stock::show(int indent)
    {
        std::cout << std::string(indent, '\t') << "Ticker: " << this->ticker << std::endl;
    }

    Company::Company(int id_value, long int n_stock_value, long int n_owned_stock_value, long int debt, Sector &sector_value)
        : id(id_value),
          n_stocks(n_stock_value),
          n_owned_stocks(n_owned_stock_value),
          debt(debt),
          sector(sector_value),
          stock(Stock(std::to_string(id_value), *this)) {}

    int Company::market_cap(const market::Market &market)
    {
        return n_stocks * stock.get_current_price(market);
    }

    Sector::Sector(std::string name_value) : name(name_value), valuation(rand() % 100) {}

}