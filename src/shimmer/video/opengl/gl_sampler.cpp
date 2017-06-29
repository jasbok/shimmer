#include "gl_sampler.hpp"
#include "gl_program.hpp"

namespace shimmer
{

gl_sampler::gl_sampler(const sampler &sampler)
{
    _extend(sampler);
}

gl_sampler::~gl_sampler()
{}

void gl_sampler::bind()
{
    glUniform1i(_location, _texture_unit);
    glActiveTexture(_texture_unit + GL_TEXTURE0);
    texture()->bind();
}

void gl_sampler::_extend(const sampler &sampler)
{
    name(sampler.name());
    texture(sampler.texture());
}

}
