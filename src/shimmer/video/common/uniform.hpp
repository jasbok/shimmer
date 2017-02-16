#ifndef SHIMMER_VIDEO_COMMON_UNIFORM_HPP
#define SHIMMER_VIDEO_COMMON_UNIFORM_HPP

#include "common/macros.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class uniform
{
public:
        uniform() {}
        virtual ~uniform() {}

        enum class type
        {
        };
private:
        SHIMMER_MEMBER ( uniform, std::string, name );
        SHIMMER_MEMBER ( uniform, enum uniform::type, type );
        SHIMMER_VOID_MEMBER ( uniform, value );
};
}

#endif
