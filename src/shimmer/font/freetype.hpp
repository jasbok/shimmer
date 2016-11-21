#ifndef SHIMMER_FONT_ERROR
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace shimmer
{
std::string freetype_string_from ( FT_Error code );
}

#endif
