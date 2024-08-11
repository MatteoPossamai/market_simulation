#pragma once

#include <map>
#include <string>
#include <iostream>
#include "constants.h"

namespace parser
{
    constants::config_t parseTOML(const std::string filename);
}