#include "file_helpers.h"

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
                while ( ( ep = readdir ( dp ) ) ){
                    std::string entry(ep->d_name);
                    if(entry.compare(".") != 0 && entry.compare("..") != 0){
                        results.push_back ( entry );
                    }
                }
                closedir ( dp );
        } else {
                printf ( "Unable to open directory: %s\n", dir );
        }

        return results;
}

std::vector<std::string> list_directory ( const std::string& dir )
{
        return list_directory ( dir.c_str() );
}
}
