#ifndef STD_HELPERS_H
#define STD_HELPERS_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

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

std::vector<std::string> list_directory ( const char* dir )
{
        std::vector<std::string> results;
        DIR *dp = opendir ( dir );

        if ( dp ) {
                struct dirent *ep;
                while ( (ep = readdir ( dp )) )
                        results.push_back ( std::string(ep->d_name) );
                closedir ( dp );
        } else {
                printf ( "Unable to open directory: %s\n", dir );
        }

        return results;
}

}

#endif
