#ifndef CONFIG_H
#define CONFIG_H

namespace shimmer
{
struct config_t {
        config_t()
                : width ( 0 ),
                  height ( 0 ),
                  use_software ( false ),
                  update_rate ( 60 ),
                  filter_level ( 0 ),
                  keep_aspect_ratio ( true )
        {}

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

        // VIDEO
        unsigned int width, height;
        bool use_software;
        unsigned int update_rate;
        unsigned int filter_level;
        bool keep_aspect_ratio;
};

typedef config_t config;
}

#endif
