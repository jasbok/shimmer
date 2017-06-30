#include "file_helpers.hpp"

namespace shimmer
{
std::string read_contents ( const char* path )
{
    std::string contents;

    try {
        std::ifstream ifs ( path );

        if ( !ifs.fail() ) {
            contents.assign ( ( std::istreambuf_iterator<char> ( ifs ) ),
                              ( std::istreambuf_iterator<char>() ) );
        } else {
            std::cerr << "File does not exist: " << path << std::endl;
        }
    } catch ( const std::exception& ex ) {
        std::cerr << "Unable to read file: " << path
                  << " (" << ex.what() << ")" << std::endl;
    }

    return contents;
}

std::string read_contents ( const std::string& path )
{
    return read_contents ( path.c_str() );
}

std::vector<std::string> list_directory ( const char* dir )
{
    std::vector<std::string> results;
    DIR* dp = opendir ( dir );

    if ( dp ) {
        struct dirent* ep;

        while ( ( ep = readdir ( dp ) ) ) {
            std::string entry ( ep->d_name );

            if ( entry.compare ( "." ) != 0 && entry.compare ( ".." ) != 0 ) {
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
