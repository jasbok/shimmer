#include "regex_helpers.hpp"
#include <iostream>

std::vector<std::string> shimmer::find_all ( const std::string& src, const std::regex& regex, unsigned int group )
{
        std::vector<std::string> group_matches;
        std::string target = src;
        std::smatch match;
        while ( std::regex_search ( target, match, regex ) ) {
                if ( match.size() > group ) {
                        group_matches.push_back ( match[group] );
                }
                target = match.suffix();
        }
        return group_matches;
}

std::vector<std::vector<std::string>> shimmer::find_all ( const std::string& src, const std::regex& regex, const std::vector<unsigned int>& groups )
{
        std::vector<std::vector<std::string>> results;
        std::string target = src;
        std::smatch match;
        while ( std::regex_search ( target, match, regex ) ) {
                std::vector<std::string> group_matches;
                for ( unsigned int group : groups ) {
                        if ( match.size() > group ) {
                                group_matches.push_back ( match[group].str() );
                        } else {
                                group_matches.push_back ( std::string() );
                        }
                }
                target = match.suffix();
                results.push_back ( group_matches );
        }
        return results;
}

std::vector<std::string> shimmer::split ( const std::string& src, const std::regex& regex )
{
        std::sregex_token_iterator first {src.begin(), src.end(), regex, -1} , last;
        return {first, last};
}

std::vector<std::string> shimmer::split ( const std::string& src, const std::string& regex )
{
        return split ( src, std::regex ( regex ) );
}

std::string shimmer::replace ( const std::string& src, const std::regex& regex, const std::string& sub )
{
        return std::regex_replace ( src, regex, sub );
}

std::string shimmer::replace ( const std::string& src, const std::string& regex, const std::string& sub )
{
        return replace ( src, std::regex ( regex ), sub );
}

std::string shimmer::transform ( const std::string& src, const std::regex& regex, const std::function<std::string ( const std::string & ) >& func )
{
        std::string ret;

        for(auto it = std::sregex_token_iterator(src.begin(), src.end(), regex, {0}); it != std::sregex_token_iterator(); it++){
                ret += (it->matched ? func(*it) : *it) + *(it->first);
        }
        return ret;
}

std::string shimmer::transform ( const std::string& src, const std::string& regex, const std::function<std::string ( const std::string & ) >& func )
{
        return transform ( src, std::regex ( regex ), func );
}

