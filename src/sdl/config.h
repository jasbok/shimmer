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
        static config &instance();

        bool toggle_keep_aspect_ratio();

        unsigned int next_filter_level();

private:
        config();

        config ( const config &conf );
        const config &operator= ( const config &conf );

        virtual ~config() {}
};
}

#endif
