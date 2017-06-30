#ifndef SHIMMER_COMMON_ENUMS_HPP
#define SHIMMER_COMMON_ENUMS_HPP

namespace shimmer
{
enum class pixel_format
{
    RGB, BGR, RGBA, BGRA
};
enum class pixel_type
{
    UNSIGNED_BYTE, BYTE, UNSIGNED_SHORT_5_6_5, UNSIGNED_SHORT_5_6_5_REV
};
}

#endif
