#pragma once

#include <string>

namespace instruments
{
    // General structures
    class Instrument
    {
    };

    struct Sector
    {
        std::string name;
    };

    // Stocks and companies
    class Stock : Instrument
    {
        public:
        std::string ticker;
        Stock(std::string);
    };

    enum CompanyType
    {
        PUBLIC,
        PRIVATE
    };

    class Company
    {
    public:
        std::string name;
        Stock stock;
        long int n_stocks;
        long int n_owned_stocks;
        long int debt;
        Sector sector;

        Company(std::string, long int, long int, long int, Sector);
        int market_cap();
    };

}