#ifndef FILE_HELPERS_HPP
#define FILE_HELPERS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

namespace shimmer
{
std::string read_contents ( const char* path );

std::string read_contents ( const std::string& path );

std::vector<std::string> list_directory ( const char* dir );

std::vector<std::string> list_directory ( const std::string& dir );
}

#endif
