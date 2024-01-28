//
// Created by Alex on 03.05.2023.
//

#include "Utilities.h"
#include <sstream>

std::vector<std::string> tokenizeFromString(const std::string& given_string, char delimiter)
{
    std::vector<std::string> resulting_tokens;
    std::stringstream ss(given_string);
    std::string token;
    while (getline(ss, token, delimiter))
        resulting_tokens.push_back(token);

    return resulting_tokens;
}
