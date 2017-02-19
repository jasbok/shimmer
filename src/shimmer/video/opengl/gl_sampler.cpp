#include "gl_sampler.hpp"
#include "gl_program.hpp"

namespace shimmer
{

gl_sampler::gl_sampler(const sampler &sampler)
{
        _extend(sampler);
        _calc_location();
}

gl_sampler::~gl_sampler()
{}

void gl_sampler::_extend(const sampler &sampler)
{
        name(sampler.name());
        texture(sampler.texture());
}

void gl_sampler::_calc_location()
{
//	if(shader()){
//		auto program = std::static_pointer_cast<gl_program>(shader());
//		location(glGetUniformLocation(program->handle(), name().c_str()));
//	}
}

}
