#include "gl_material.hpp"
#include "gl_program.hpp"
#include "gl_sampler.hpp"
#include <GL/glew.h>
#include <memory>

namespace shimmer
{
gl_material::gl_material(const material& mat)
{
        _extend(mat);
}

gl_material::~gl_material()
{}

void gl_material::use()
{
        shader()->use();

        unsigned int i = 0;
        for(auto sampler :  samplers()) {
                if(sampler) {
                        auto location = std::static_pointer_cast<gl_sampler>(sampler)->location();
                        glUniform1i(location, i);
                        glActiveTexture(GL_TEXTURE0 + i++);
                        sampler->texture()->bind();
                }
        }
}

void gl_material::_extend(const material &mat)
{
        shader(mat.shader());
        samplers(mat.samplers());
}

}
