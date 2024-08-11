#pragma once
#include <string>
#include <vector>
#include <variant>
#include "actors.h"
#include "instruments.h"

namespace market
{

    // Order
    struct MarketOrder
    {
    };
    struct LimitOrder
    {
        float price;
    };
    using OrderType = std::variant<MarketOrder, LimitOrder>;

    struct Order
    {
        public:
        actors::Actor &issuer;
        OrderType type;
        instruments::Instrument &instrument;
        int quantity;
        int time;

        Order(actors::Actor &, OrderType, instruments::Instrument &, int, int);
    };

    // Market
    class Market
    {
    public:
        std::string name;
        std::vector<Order> orders;

        Market(std::string);
    };
}