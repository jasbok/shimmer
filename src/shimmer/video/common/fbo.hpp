#ifndef SHIMMER_VIDEO_COMMON_FBO_HPP
#define SHIMMER_VIDEO_COMMON_FBO_HPP

#include "common/macros.hpp"
#include "texture.hpp"
#include <memory>
#include <vector>

namespace shimmer
{
class fbo
{
public:
private:
        typedef std::vector<std::shared_ptr<shimmer::texture>> texture_vec;
        SHIMMER_MEMBER(fbo, texture_vec, colour_attachments);
};
}

#endif
