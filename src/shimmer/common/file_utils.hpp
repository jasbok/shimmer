#ifndef SHIMMER_COMMON_FILE_UTILS_HPP
#define SHIMMER_COMMON_FILE_UTILS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

namespace shimmer
{
namespace file_utils
{
        std::string read_contents ( const char* path );
        std::string read_contents ( const std::string& path );
        std::vector<std::string> list_directory ( const char* dir );
        std::vector<std::string> list_directory ( const std::string& dir );
};
}

#endif
