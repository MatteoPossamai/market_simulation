#include "market.h"
#include "actors.h"
#include "instruments.h"
#include <string>

namespace market
{
    Order::Order(actors::Actor &actor, OrderType order_type, instruments::Instrument &instrument, int quantity_value, int time_value)
        : issuer(actor),
          type(order_type),
          instrument(instrument),
          quantity(quantity_value),
          time(time_value) {}

    Market::Market(std::string name_value)
        : name(name_value) {}
}