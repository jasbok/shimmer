#ifndef SHIMMER_VIDEO_OPENGL_GL_UNIFORM_HPP
#define SHIMMER_VIDEO_OPENGL_GL_UNIFORM_HPP

#include "video/common/uniform.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_uniform : public uniform
{
public:
        gl_uniform(const uniform& uniform);
        virtual ~gl_uniform();

        virtual uniform& value(const std::string& value);
        virtual uniform& value(std::string&& value);

protected:
        virtual void _parse(const std::string& str);
private:
        SHIMMER_MEMBER(gl_uniform, GLint, location);

        void _extend(const uniform& uniform);
};

}
#endif
