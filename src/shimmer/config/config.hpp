#ifndef SHIMMER_CONFIG_HPP
#define SHIMMER_CONFIG_HPP

#include <string>
#include <map>
#include <vector>

namespace shimmer
{
class config
{
public:
    config();

    config ( const config& conf );

    config ( config&& move );

    virtual ~config() {}

    config& operator= ( const config& copy );

    config& operator= ( config &&move );

    std::string& operator[] ( const std::string& key );

    bool exists ( const std::string& key );

    bool read_bool ( const std::string& key );

    char read_char ( const std::string& key );

    int read_int ( const std::string& key );

    float read_float ( const std::string& key );

    std::string read_str ( const std::string& key );

    std::vector<std::string> read_strs (
        const std::string& key,
        const std::string& split = "\\s+" );

    std::vector<int> read_ints (
        const std::string& key,
        const std::string& split = "\\s+" );

    std::vector<float> read_floats (
        const std::string& key,
        const std::string& split = "\\s+" );

    bool is_value ( const std::string& key, char value );

    bool is_value ( const std::string& key, float value );

    bool is_value ( const std::string& key, const std::string& value );

    bool is_value ( const std::string& key, int value );

    config& write ( const std::string& key, bool value );

    config& write ( const std::string& key, char value );

    config& write ( const std::string& key, const std::string& value );

    template <typename T>
    config& write ( const std::string& key, const T& value )
    {
        _map[key] = std::to_string ( value );
        return *this;
    }

    auto begin() const
    {
        return _map.begin();
    }

    auto end() const
    {
        return _map.end();
    }

private:
    std::map<std::string, std::string> _map;
};
}

#endif
