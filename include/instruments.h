#pragma once

namespace instruments
{
    struct Company;
    class Instrument;
    struct Sector;
    class Stock;
}

#include <string>
#include "market.h"
namespace instruments
{
    // General structures
    class Instrument
    {
    public:
        virtual void show(std::string) = 0;
        virtual ~Instrument() = default;
    };

    struct Sector
    {
        std::string name;
        double valuation;
        Sector(std::string);
        bool operator=(const Sector &other) const
        {
            return this->name == other.name;
        }
        bool operator<(const Sector &other) const
        {
            return this->name < other.name;
        }
        bool operator>(const Sector &other) const
        {
            return this->name > other.name;
        }
    };

    // Stocks and companies
    class Stock : public Instrument
    {
    private:
    public:
        std::shared_ptr<Stock> self;
        std::string ticker;
        const Company &company;
        Stock(std::string, const Company &);
        double get_current_price(const market::Market &);
        void show(std::string);
        bool operator=(const Stock &other) const
        {
            return this->ticker == other.ticker;
        }
        bool operator<(const Stock &other) const
        {
            return this->ticker < other.ticker;
        }
        bool operator>(const Stock &other) const
        {
            return this->ticker > other.ticker;
        }
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
        int id;
        Stock stock;
        long int n_stocks;
        long int n_owned_stocks;
        long int debt;
        Sector &sector;

        Company(int id, long int, long int, long int, Sector &);
        int market_cap(const market::Market &);
        bool operator=(const Company &other) const
        {
            return this->id == other.id;
        }
        bool operator<(const Company &other) const
        {
            return this->id < other.id;
        }
        bool operator>(const Company &other) const
        {
            return this->id > other.id;
        }
    };

};