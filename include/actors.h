#pragma once
#include "instruments.h"
#include <map>
#include <string>

namespace actors
{
    using portfolio_t = std::map<instruments::Instrument, int>;

    // Base actors
    class Actor
    {
        int id;
        std::string name;
        float risk_adversity;
        int age;
        int execution_pace;
        int cash;

    public:
        portfolio_t portfolio;

        Actor(int, std::string, float, int, int, int);
    };
}