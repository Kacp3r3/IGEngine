#pragma once
#include <string>
#include <sstream>

class StringUtil
{
public:
    template <class Container>
    static void split(const std::string& str, Container& cont, char delim =' ')
    {
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            cont.push_back(token);
        }
    }
};

