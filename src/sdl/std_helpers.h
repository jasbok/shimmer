#ifndef STD_HELPERS_H
#define STD_HELPERS_H

#include <fstream>
#include <string>
#include <iostream>

namespace shimmer
{
std::string read_contents ( const char* file )
{
        std::ifstream ifs ( file );
        std::string contents;
        if ( !ifs.fail() ) {
                contents.assign ( ( std::istreambuf_iterator<char> ( ifs ) ),
                                  ( std::istreambuf_iterator<char>() ) );
        } else {
                std::cerr << "File does not exist: " << file << std::endl;
        }
        return contents;
}
}

#endif
