#include "actors.h"
#include "market.h"
#include <string>

namespace actors
{
  Actor::Actor(int id_value, double risk_adversity_value, int age_value, int execution_pace_value, double cash_value)
      : id(id_value),
        risk_adversity(risk_adversity_value),
        age(age_value),
        execution_pace(execution_pace_value),
        cash(cash_value) {}

  void Actor::buy(market::Market &interest_market, instruments::Stock &instrument, market::OrderType order_type, int quantity, double price = 0)
  {
    if (order_type == market::LIMIT_ORDER && price <= 0)
    {
      throw std::invalid_argument("LIMIT_ORDER requires a valid price greater than 0.");
    }
    else if (order_type == market::LIMIT_ORDER)
    {
      interest_market.add_buy_order(*this, order_type, instrument, quantity, price);
    }
    else
    {
      // TODO: fill the order
    }
  }
  void Actor::sell(market::Market &interest_market, instruments::Stock &instrument, market::OrderType order_type, int quantity, double price = 0)
  {
    if (order_type == market::LIMIT_ORDER && price <= 0)
    {
      throw std::invalid_argument("LIMIT_ORDER requires a valid price greater than 0.");
    }
    else if (order_type == market::LIMIT_ORDER)
    {
      interest_market.add_sell_order(*this, order_type, instrument, quantity, price);
    }
    else
    {
      // TODO: fill the order
    }
  }
}