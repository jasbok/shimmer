#ifndef SHIMMER_VIDEO_OPENGL_UNIFORMS_APPLICATION_OUTPUT
#define SHIMMER_VIDEO_OPENGL_UNIFORMS_APPLICATION_OUTPUT

#include "uniform_output.hpp"
#include <GL/glew.h>

namespace shimmer
{
class application_output : public uniform_output
{
public:
        application_output(GLint location, GLuint texture);
        virtual ~application_output();
        void process() override;
private:
        GLuint _texture;
};
}

#endif
