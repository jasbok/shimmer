#ifndef SHIMMER_VIDEO_OPENGL_GL_PROGRAM_HPP
#define SHIMMER_VIDEO_OPENGL_GL_PROGRAM_HPP

#include "video/common/shader.hpp"
#include "gl_shader.hpp"
#include "gl_uniform.hpp"
#include <GL/glew.h>
#include <memory>
#include <unordered_map>
#include <vector>

namespace shimmer
{
class gl_program : public shader
{
private:
        typedef std::vector<std::shared_ptr<gl_shader>> gl_shaders;

public:
        gl_program (
                const shader& shader,
                const gl_shaders &gl_vertex_shaders,
                const gl_shaders &gl_fragment_shaders );

        gl_program (
                const shader& shader,
                gl_shaders &&gl_vertex_shaders,
                gl_shaders &&gl_fragment_shaders );

        virtual ~gl_program();

        virtual void use();
private:
        SHIMMER_MEMBER ( gl_program, gl_shaders, gl_vertex_shaders );
        SHIMMER_MEMBER ( gl_program, gl_shaders, gl_fragment_shaders );
        SHIMMER_GETTER ( gl_program, GLuint, handle );

        void _extend ( const shader& shader );
        std::vector<gl_shaders> _all_shaders();
        void _link_program ();
        void _parse_variables (const std::shared_ptr<gl_shader>& shader);
        void _print_errors();
};
}

#endif
