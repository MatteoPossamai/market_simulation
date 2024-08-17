#pragma once
#include <memory>
#include <string>
#include <vector>

namespace market
{
    class Market;
    struct Order;
    typedef enum OrderType
    {
        MARKET_ORDER,
        LIMIT_ORDER
    } OrderType;
}

#include <bits/stdc++.h>
#include "actors.h"
#include "instruments.h"

namespace market
{

    // Order
    struct Order
    {
    public:
        int id;
        actors::Actor &issuer;
        OrderType type;
        instruments::Stock &instrument;
        int quantity;
        int time;
        int price;
        bool active;

        Order(int, actors::Actor &, OrderType, instruments::Stock &, int, int);
        bool operator=(const Order &other) const
        {
            return this->price == other.price;
        }
        bool operator<(const Order &other) const
        {
            return this->price < other.price;
        }
        bool operator>(const Order &other) const
        {
            return this->price > other.price;
        }
    };

    // Market
    class Market
    {
        int counter;
        std::map<int, std::shared_ptr<Order>> orders;

    public:
        std::string name;
        std::map<instruments::Stock *, std::priority_queue<std::shared_ptr<Order>>> buy_orders;
        std::map<instruments::Stock *, std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, std::greater<std::shared_ptr<Order>>>> sell_orders;

        Market(std::string);
        int add_buy_order(actors::Actor &, OrderType, instruments::Stock &, int, int);
        int add_sell_order(actors::Actor &, OrderType, instruments::Stock &, int, int);
        std::shared_ptr<Order> get_order(int);
    };
}