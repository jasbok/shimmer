#ifndef SHIMMER_VIDEO_COMMON_SAMPLER_HPP
#define SHIMMER_VIDEO_COMMON_SAMPLER_HPP

#include "common/macros.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class sampler
{
public:
        virtual ~sampler() {}
        virtual void bind() {}
private:
        SHIMMER_MEMBER ( sampler, std::string, id );
        SHIMMER_MEMBER ( sampler, std::string, name );
        SHIMMER_MEMBER ( sampler, std::shared_ptr<shimmer::texture>, texture );
};
}

#endif
