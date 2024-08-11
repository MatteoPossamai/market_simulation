#pragma once

#include <map>
#include <string>
#include <iostream>

namespace parser
{
    std::map<std::string, std::map<std::string, std::string>> parseTOML(const std::string filename);
}