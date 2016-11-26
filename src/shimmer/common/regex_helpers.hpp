#ifndef REGEX_HELPERS_HPP
#define REGEX_HELPERS_HPP

#include <regex>
#include <string>
#include <vector>

namespace shimmer
{
std::vector<std::string> find_all ( const std::string& src, const std::regex& regex, unsigned int group );
std::vector<std::vector<std::string>> find_all ( const std::string& src, const std::regex& regex, const std::vector<unsigned int>& groups );
std::vector<std::string> split(const std::string& src, const std::regex& regex);
}

#endif
