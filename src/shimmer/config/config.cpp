#include "config.hpp"
#include "common/regex_helpers.hpp"
#include <algorithm>
#include <iostream>

namespace shimmer
{
config::config()
    : _map ( {
    {"paths.data", "/usr/local/libshimmer"},
    {"paths.fonts", "/usr/local/libshimmer/fonts"},
    {"paths.shaders", "/usr/local/libshimmer/shaders"},

    {"video.resolution.width", "0"},
    {"video.resolution.height", "0"},
    {"video.refresh_rate", "59"},
    {"video.fullscreen", "false"},

    {"renderer.aspect_ratio", "original"},
    {"renderer.texture.filter", "nearest"},

    {"renderer.foreground.vertex", "/usr/local/libshimmer/shaders/surface/vs/default.vert"},
    {"renderer.foreground.fragment", "/usr/local/libshimmer/shaders/surface/fs/xbrz4x.frag"},

    {"renderer.background.enabled", "false"},
    {"renderer.background.vertex", "/usr/local/libshimmer/shaders/surface/vs/default.vert"},
    {"renderer.background.fragment", "/usr/local/libshimmer/shaders/surface/fs/default.frag"},

    {"renderer.menu.vertex", "/usr/local/libshimmer/shaders/surface/vs/default.vert"},
    {"renderer.menu.fragment", "/usr/local/libshimmer/shaders/surface/fs/solid.frag"},

    {"renderer.font.regular", "/usr/local/libshimmer/fonts/xolonium/ttf/Xolonium-Regular.ttf"},
    {"renderer.font.bold", "/usr/local/libshimmer/fonts/xolonium/ttf/Xolonium-Bold.ttf"},
    {"renderer.font.size", "15"},

    {"renderer.font.vertex", "/usr/local/libshimmer/shaders/text/text.vert"},
    {"renderer.font.fragment", "/usr/local/libshimmer/shaders/text/text.frag"}
} )
{}

config::config ( const config& copy )
    : _map ( copy._map )
{}

config::config ( config&&  move )
    : _map ( std::move ( move._map ) )
{}

config& config::operator= ( const config& copy )
{
    this->_map = copy._map;
    return *this;
}

config& config::operator= ( config && move )
{
    this->_map = std::move ( move._map );
    return *this;
}

std::string& config::operator[] ( const std::string& key )
{
    return _map[key];
}

bool config::exists ( const std::string& key )
{
    return _map.find ( key ) != _map.end();
}

bool config::read_bool ( const std::string& key )
{
    std::string str = read_str ( key );
    std::transform ( str.begin(), str.end(), str.begin(), ::tolower );

    return str.compare ( "true" ) == 0;
}

char config::read_char ( const std::string& key )
{
    if ( exists ( key ) && !_map[key].empty() ) {
        return _map[key].at ( 0 );
    }

    return 0;
}

int config::read_int ( const std::string& key )
{
    int ret = 0;

    if ( exists ( key ) ) {
        auto value = _map[key];
        try {
            ret = std::stoi ( value );
        } catch ( ... ) {
            std::cerr << "Could not parse key-value to integer: "
                      << key << " = " << value << std::endl;
        }
    }

    return ret;
}

float config::read_float ( const std::string& key )
{
    float ret = 0;

    if ( exists ( key ) ) {
        auto value = _map[key];
        try {
            ret = std::stof ( value );
        } catch ( ... ) {
            std::cerr << "Could not parse key-value to float: "
                      << key << " = " << value << std::endl;
        }
    }

    return ret;
}

std::string config::read_str ( const std::string& key )
{
    if ( exists ( key ) ) {
        return _map[key];
    }

    return "";
}

std::vector<std::string> config::read_strs (
    const std::string& key,
    const std::string& regex )
{
    if ( exists ( key ) ) return split ( _map[key], regex );
    return {};
}

std::vector<int> config::read_ints (
    const std::string& key,
    const std::string& split )
{
    std::vector<int> ret;

    for ( auto str : read_strs ( key, split ) ) {
        try {
            ret.push_back ( std::stoi ( str ) );
        } catch ( ... ) {
            std::cerr << "Could not parse key-value to integer: "
                      << key << " = " << str << std::endl;
        }
    }

    return ret;
}

std::vector<float> config::read_floats (
    const std::string& key,
    const std::string& split )
{
    std::vector<float> ret;

    for ( auto str : read_strs ( key, split ) ) {
        try {
            ret.push_back ( std::stof ( str ) );
        } catch ( ... ) {
            std::cerr << "Could not parse key-value to float: "
                      << key << " = " << str << std::endl;
        }
    }

    return ret;
}

bool config::is_value ( const std::string& key, char value )
{
    return exists ( key ) && ( read_char ( key ) == value );
}

bool config::is_value ( const std::string& key, int value )
{
    return exists ( key ) && ( read_int ( key ) == value );
}

bool config::is_value ( const std::string& key, float value )
{
    return exists ( key ) && ( read_float ( key ) == value );
}

bool config::is_value ( const std::string& key, const std::string& value )
{
    return exists ( key ) && ( _map[key].compare ( value ) == 0 );
}

config& config::write ( const std::string& key, bool value )
{
    _map[key] = value ? "true" : "false";
    return *this;
}

config& config::write ( const std::string& key, char value )
{
    _map[key] = {value};
    return *this;
}

config& config::write ( const std::string& key, const std::string& value )
{
    _map[key] = value;
    return *this;
}

}
