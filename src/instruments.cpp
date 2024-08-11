#include "instruments.h"
#include <string>

namespace instruments
{
    Stock::Stock(std::string ticker_name)
        : ticker(ticker_name) {}

    Company::Company(std::string name_value, long int n_stock_value, long int n_owned_stock_value, long int debt, Sector sector_value)
        : name(name_value),
          n_stocks(n_stock_value),
          n_owned_stocks(n_owned_stock_value),
          debt(debt),
          sector(sector_value),
          stock(Stock(name_value)) {}

    int Company::market_cap()
    {
        // TODO: understand what is the right meaning and the calculation
        return 0;
    }
}