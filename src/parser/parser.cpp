#include "parser.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

namespace parser
{
    std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }

    std::map<std::string, std::map<std::string, std::string>> parseTOML(const std::string filename)
    {
        std::ifstream file(filename);
        std::map<std::string, std::map<std::string, std::string>> config;
        std::string section, key, value, line;

        while (std::getline(file, line))
        {
            line = trim(line);

            if (line.empty() || line[0] == ';' || line[0] == '#')
            {
                continue;
            }

            if (line[0] == '[' && line.back() == ']')
            {
                section = line.substr(1, line.size() - 2);
            }
            else
            {
                size_t equal_position = line.find("=");
                key = line.substr(0, equal_position);
                value = line.substr(equal_position + 1, line.size() - 1);
                config[section][key] = value;
            }
        }

        return config;
    }
}
