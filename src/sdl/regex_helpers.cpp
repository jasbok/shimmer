#include "regex_helpers.h"

std::vector<std::string> shimmer::find_all(const std::string& src, const std::regex& regex, unsigned int group)
{
        std::vector<std::string> group_matches;
        std::string target = src;
        std::smatch match;
        while(std::regex_search(target, match, regex)){
                if(match.size() > group){
                        group_matches.push_back(match[group]);
                        target = match.suffix();
                }
        }
        return group_matches;
}
