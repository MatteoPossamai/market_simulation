#include "parser.h"
#include <string>

int main()
{
    const std::string filename = "./config/example1.toml";
    auto config_map = parser::parseTOML(filename);

    for (auto it = config_map.cbegin(); it != config_map.cend(); ++it)
    {
        std::cout << it->first << " ";
        for (auto second = it->second.cbegin(); second != it->second.cend(); second++)
        {
            std::cout << second->first << " " << second->second << "\n";
        }
    }
    return 0;
}