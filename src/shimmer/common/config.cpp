#include "config.hpp"

shimmer::config & shimmer::config::instance()
{
        static config *instance = new config;
        return *instance;
}

bool shimmer::config::toggle_keep_aspect_ratio()
{
        keep_aspect_ratio = !keep_aspect_ratio;
        return keep_aspect_ratio;
}

unsigned int shimmer::config::next_filter_level()
{
        filter_level = ++filter_level <= 1 ? filter_level : 0;
        return filter_level;
}

shimmer::config::config()
        : width ( 0 ), height ( 0 ),
          update_rate ( 59 ),
          filter_level ( 0 ),
          keep_aspect_ratio ( true ),
          data_prefix ( DATA_PREFIX ),
          shaders_prefix ( SHADERS_PREFIX ),
          vertex_shader ( "default.vert" ),
          fragment_shader ( "default.frag" )
{}
