#ifndef SHIMMER_VIDEO_OPENGL_GL_SAMPLER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_SAMPLER_HPP

#include "common/macros.hpp"
#include "video/common/sampler.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_sampler : public sampler
{
public:
    gl_sampler(const sampler& sampler);
    virtual ~gl_sampler();

    virtual void bind();
private:
    SHIMMER_MEMBER(gl_sampler, GLuint, texture_unit);
    SHIMMER_MEMBER(gl_sampler, GLint, location);

    void _extend(const sampler& sampler);
};
}

#endif
