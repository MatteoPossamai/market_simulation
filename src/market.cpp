#include "market.h"
#include "actors.h"
#include "instruments.h"
#include <string>
#include <memory>

namespace market
{
  Order::Order(int id_val, actors::Actor &actor, OrderType order_type, instruments::Stock &instrument, int quantity_value, int price_val)
      : issuer(actor),
        type(order_type),
        instrument(instrument),
        quantity(quantity_value),
        price(0),
        id(id_val)
  {
    active = true;
    if (order_type == LIMIT_ORDER)
    {
      price = price_val; // Set price only if it's a LIMIT_ORDER
    }
  }

  Market::Market(std::string name_value)
      : name(name_value), counter(0) {}

  int Market::add_buy_order(actors::Actor &actor, OrderType type, instruments::Stock &instrument, int quantity, int price)
  {
    auto order = std::make_shared<Order>(++this->counter, actor, type, instrument, quantity, price);
    if (!this->buy_orders.count(&instrument))
    {
      this->buy_orders.insert({&instrument, {}});
    }
    buy_orders[&instrument].push(order);
    orders[counter] = order;
    return this->counter;
  }

  int Market::add_sell_order(actors::Actor &actor, OrderType type, instruments::Stock &instrument, int quantity, int price)
  {
    auto order = std::make_shared<Order>(++this->counter, actor, type, instrument, quantity, price);
    if (!this->sell_orders.count(&instrument))
    {
      this->sell_orders.insert({&instrument, {}});
    }
    buy_orders[&instrument].push(order);
    orders[counter] = order;
    return counter;
  }

  std::shared_ptr<Order> Market::get_order(int orderId)
  {
    if (orders.find(orderId) == orders.end())
    {
      throw std::out_of_range("Order ID not found");
    }
    return orders[orderId];
  }
}