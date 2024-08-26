#include "market.h"
#include "actors.h"
#include "instruments.h"
#include <string>
#include <memory>
#include <limits>

namespace market
{
  Order::Order(int id_val, actors::Actor &actor, OrderType order_type, std::shared_ptr<instruments::Stock> instrument, int quantity_value, double price_val)
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

  int Market::add_buy_order(actors::Actor &actor, OrderType type, std::shared_ptr<instruments::Stock> instrument, int quantity, double price)
  {
    if (type == OrderType::MARKET_ORDER)
    {
      price = std::numeric_limits<int>::max();
      std::cout << "MARKET BUY ORDER FOR:" << std::endl;
    }
    else
    {
      std::cout << "LIMIT BUY ORDER FOR:" << std::endl;
    }

    instrument.get()->show("");
    while (quantity > 0 && this->sell_orders.at(instrument).size() > 0 && actor.get_cash() > 0)
    {
      std::shared_ptr<market::Order> top_sell = this->sell_orders.at(instrument).top();

      while (sell_orders.at(instrument).size() > 0 && !top_sell.get()->active)
      {
        this->sell_orders.at(instrument).pop();
        top_sell = this->sell_orders.at(instrument).top();
      }

      if (top_sell.get()->price > price && type == OrderType::LIMIT_ORDER)
      {
        auto order = std::make_shared<Order>(++this->counter, actor, type, instrument, quantity, price);
        if (!this->sell_orders.count(instrument))
        {
          this->sell_orders.insert({instrument, {}});
        }
        buy_orders[instrument].push(order);
        orders[counter] = order;
        return counter;
      }

      int b_quantity = std::min(quantity, top_sell.get()->quantity);
      double paid_price = top_sell.get()->price * b_quantity;

      if (actor.get_cash() < paid_price)
      {
        return 0;
      }

      actors::Actor &counter_party = top_sell.get()->issuer;
      if (counter_party.portfolio.count(instrument) && counter_party.portfolio.at(instrument) < b_quantity)
      {
        b_quantity = counter_party.portfolio.at(instrument);
      }

      // Exchange of cash and stocks after validity checks
      counter_party.portfolio.at(instrument) -= b_quantity;
      counter_party.set_cash(counter_party.get_cash() + paid_price);
      actor.set_cash(actor.get_cash() - paid_price);
      if (!actor.portfolio.at(instrument))
      {
        actor.portfolio.at(instrument) = 0;
      }
      actor.portfolio.at(instrument) = actor.portfolio.at(instrument) + b_quantity;

      quantity -= b_quantity;
    }
    return 0;
  }

  int Market::add_sell_order(actors::Actor &actor, OrderType type, std::shared_ptr<instruments::Stock> instrument, int quantity, double price)
  {
    if (type == OrderType::MARKET_ORDER)
    {
      price = std::numeric_limits<int>::max();
      std::cout << "MARKET SELL ORDER FOR:" << std::endl;
    }
    else
    {
      std::cout << "LIMIT SELL ORDER FOR:" << std::endl;
    }

    instrument.get()->show("");
    while (quantity > 0 && this->buy_orders.at(instrument).size() > 0 && actor.get_cash() > 0)
    {
      std::shared_ptr<market::Order> top_buy = this->buy_orders.at(instrument).top();

      while (buy_orders.at(instrument).size() > 0 && !top_buy.get()->active)
      {
        this->buy_orders.at(instrument).pop();
        top_buy = this->sell_orders.at(instrument).top();
      }

      if (top_buy.get()->price < price && type == OrderType::LIMIT_ORDER)
      {
        auto order = std::make_shared<Order>(++this->counter, actor, type, instrument, quantity, price);
        if (!this->sell_orders.count(instrument))
        {
          this->sell_orders.insert({instrument, {}});
        }
        sell_orders[instrument].push(order);
        orders[counter] = order;
        return counter;
      }

      int b_quantity = std::min(quantity, top_buy.get()->quantity);
      double paid_price = top_buy.get()->price * b_quantity;

      if (actor.get_cash() < paid_price)
      {
        return 0;
      }

      // TODO: fix the conversion of the sell order thingy
      actors::Actor &counter_party = top_buy.get()->issuer;
      if (counter_party.portfolio.count(instrument) && counter_party.portfolio.at(instrument) < b_quantity)
      {
        b_quantity = counter_party.portfolio.at(instrument);
      }

      // Exchange of cash and stocks after validity checks
      counter_party.portfolio.at(instrument) -= b_quantity;
      counter_party.set_cash(counter_party.get_cash() + paid_price);
      actor.set_cash(actor.get_cash() - paid_price);
      if (!actor.portfolio.at(instrument))
      {
        actor.portfolio.at(instrument) = 0;
      }
      actor.portfolio.at(instrument) = actor.portfolio.at(instrument) + b_quantity;

      quantity -= b_quantity;
    }
    return 0;
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