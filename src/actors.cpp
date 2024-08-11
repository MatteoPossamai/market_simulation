#include "actors.h"
#include <string>

namespace actors
{
    Actor::Actor(int id_value, std::string name_value, float risk_adversity_value, int age_value, int execution_pace_value, int cash_value)
        : id(id_value),
          name(name_value),
          risk_adversity(risk_adversity_value),
          age(age_value),
          execution_pace(execution_pace_value),
          cash(cash_value) {}
}