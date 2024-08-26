#include "actors.h"
#include "market.h"
#include <string>
#include <time.h>

namespace actors
{
  Actor::Actor(int id_value, double risk_adversity_value, int execution_pace_value, double cash_value)
      : id(id_value),
        risk_adversity(risk_adversity_value),
        execution_pace(execution_pace_value),
        cash(cash_value) {}

  void Actor::buy(market::Market &interest_market, std::shared_ptr<instruments::Stock> instrument, market::OrderType order_type, int quantity, double price = 0)
  {
    std::cout << "[Actor:" << this->id << "]" << "BUYING " << instrument.get()->ticker << " FOR " << price << std::endl;
    if (order_type == market::LIMIT_ORDER && price <= 0)
    {
      throw std::invalid_argument("LIMIT_ORDER requires a valid price greater than 0.");
    }
    else if (order_type == market::LIMIT_ORDER)
    {
      this->active_orders.push_back(interest_market.add_buy_order(*this, order_type, instrument, quantity, price));
    }
    else
    {
      while (quantity > 0)
      {
        auto best_sell = interest_market.sell_orders.at(instrument).top().get();
        interest_market.add_buy_order(*this, order_type, instrument, std::min(best_sell->quantity, quantity), best_sell->price);
      }
    }
  }

  void Actor::sell(market::Market &interest_market, std::shared_ptr<instruments::Stock> instrument, market::OrderType order_type, int quantity, double price = 0)
  {
    std::cout << "[Actor:" << this->id << "]" << "Selling" << std::endl;
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
      while (quantity > 0)
      {
        auto best_buy = interest_market.sell_orders.at(instrument).top().get();
        interest_market.add_sell_order(*this, order_type, instrument, std::min(best_buy->quantity, quantity), best_buy->price);
        quantity -= best_buy->quantity;
      }
    }
  }

  void Actor::act(const information::NewsStream &news_stream, std::vector<std::shared_ptr<instruments::Company>> companies, market::Market &market)
  {
    // Portfolio management

    auto portfolio_iter = this->portfolio.begin();
    while (portfolio_iter != this->portfolio.end())
    {
      const std::shared_ptr<instruments::Company> company = portfolio_iter->first->company;
      double sentiment = inspect(portfolio_iter->first->company, news_stream);

      double value = this->risk_adversity * sentiment;

      auto stock = portfolio_iter->first;
      double price = stock->get_current_price(market, 0, 0, 0);
      if (value < 15)
      {
        sell(market, stock, market::MARKET_ORDER, portfolio_iter->second);
      }
      else if (value < 40)
      {
        if (rand() % 2)
        {
          sell(market, stock, market::LIMIT_ORDER, portfolio_iter->second / 2, price + (price * value / 1000));
        }
        else
        {
          double available = this->cash / this->risk_adversity;
          int quantity = std::max(0, (int)(price / available) - 5);
          buy(market, stock, market::LIMIT_ORDER, quantity, price - (price * value / 1000));
        }
      }
      else if (value > 65)
      {
        double available = this->cash / this->risk_adversity;
        int quantity = price / available;
        sell(market, stock, market::MARKET_ORDER, quantity);
      }
    }

    // Buy check
    int checks = this->execution_pace;
    for (int i = 0; i < checks; i++)
    {
      auto random_company = companies.at(rand() % companies.size());
      double sentiment = inspect(random_company, news_stream);
      auto cmp = random_company.get();
      int stock, owned, debt;
      stock = cmp->n_stocks;
      owned = cmp->n_owned_stocks;
      debt = cmp->debt;
      int current_price = random_company.get()->stock.get()->get_current_price(market, stock, owned, debt); 
      double available = this->cash / this->risk_adversity;
      int quantity = std::max(0, (int)available / current_price);
      double value = this->risk_adversity * sentiment;

      if (value > 40 && value < 70 && quantity != 0)
      {
        buy(market, random_company.get()->stock.get()->self, market::LIMIT_ORDER, quantity, current_price - (current_price * value / 1000));
      }
      else if (value > 70 && quantity != 0)
      {
        buy(market, random_company.get()->stock.get()->self, market::MARKET_ORDER, quantity, 0);
      }
    }
  }

  double Actor::inspect(const std::shared_ptr<instruments::Company> company, const information::NewsStream &news_stream)
  {
    int news_available = this->execution_pace;
    int idx = news_stream.company_sentiment.count(company) ? news_stream.company_sentiment.at(company).size() - 1 : -1;
    int times = 0;
    double sentiment = 0.0;
    while (idx >= 0 && news_available > 0)
    {
      auto value = news_stream.company_sentiment.at(company).at(idx);
      times += value.first;
      sentiment += value.second * value.first;
      news_available--;
      idx--;
    }
    double company_sentiment;
    double sector_sentiment = this->inspect(company.get()->sector, news_stream);
    if (times == 0)
    {
      company_sentiment = 0.5;
    }
    else
    {
      company_sentiment = sentiment / times;
    }
    double return_value = company_sentiment * 0.7 + sector_sentiment * 0.3;
    return return_value;
  }
  double Actor::inspect(const instruments::Sector &sector, const information::NewsStream &news_stream)
  {
    int news_available = this->execution_pace;
    int idx = news_stream.sector_sentiment.count(sector) ? news_stream.sector_sentiment.at(sector).size() - 1 : -1;
    int times = 0;
    double sentiment = 0.0;
    while (idx >= 0 && news_available > 0)
    {
      auto value = news_stream.sector_sentiment.at(sector).at(idx);
      times += value.first;
      sentiment += value.second * value.first;
      news_available--;
      idx--;
    }
    if (times == 0)
    {
      return 0.5;
    }
    else
    {
      return sentiment / times;
    }
  }
}