#ifndef CONFIG_H
#define CONFIG_H

#ifndef DATA_PREFIX
#define DATA_PREFIX "/usr/local/libshimmer"
#endif

#ifndef SHADERS_PREFIX
#define SHADERS_PREFIX "/usr/local/libshimmer/shaders"
#endif

#include <string>

namespace shimmer
{
class config
{
public:
        // VIDEO
        unsigned int width, height;
        unsigned int update_rate;
        unsigned int filter_level;
        bool keep_aspect_ratio;

        // FILESYSTEM
        std::string data_prefix;
        std::string shaders_prefix;

        // SHADERS
        std::string vertex_shader;
        std::string fragment_shader;

public:
        static config &instance()
        {
                static config *instance = new config;
                return *instance;
        }

        bool toggle_keep_aspect_ratio()
        {
                keep_aspect_ratio = !keep_aspect_ratio;
                return keep_aspect_ratio;
        }

        unsigned int next_filter_level()
        {
                filter_level = ++filter_level <= 1 ? filter_level : 0;
                return filter_level;
        }

private:
        config()
                : width ( 0 ), height ( 0 ),
                  update_rate ( 59 ),
                  filter_level ( 0 ),
                  keep_aspect_ratio ( true ),
                  data_prefix ( DATA_PREFIX ),
                  shaders_prefix ( SHADERS_PREFIX ),
                  vertex_shader ( "default.vert" ),
                  fragment_shader ( "hsv.frag" )
        {}

        config ( const config &conf );
        const config &operator= ( const config &conf );

        ~config() {}
};
}

#endif
