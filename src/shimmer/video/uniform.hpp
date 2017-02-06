#ifndef SHIMMER_VIDEO_UNIFORM_HPP
#define SHIMMER_VIDEO_UNIFORM_HPP

#include "common/macros.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class uniform
{
public:
        enum class type{
        };
private:
        SHIMMER_MEMBER(uniform, std::string, name);
        SHIMMER_MEMBER(uniform, enum uniform::type, type);
        SHIMMER_VOID_MEMBER(uniform, value);
};
}

#endif
