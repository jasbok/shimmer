#ifndef REGEX_HELPERS_H
#define REGEX_HELPERS_H

#include <regex>
#include <string>
#include <vector>

namespace shimmer
{
std::vector<std::string> find_all ( const std::string& src, const std::regex& regex, unsigned int group );
std::vector<std::vector<std::string>> find_all ( const std::string& src, const std::regex& regex, const std::vector<unsigned int>& groups );
}

#endif
