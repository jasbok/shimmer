#ifndef SHIMMER_VIDEO_OPENGL_UNIFORMS_UNIFORM_OUTPUT
#define SHIMMER_VIDEO_OPENGL_UNIFORMS_UNIFORM_OUTPUT

#include "common/macros.hpp"
#include <GL/glew.h>

namespace shimmer
{
class uniform_output
{
public:
    virtual void process() = 0;

    virtual ~uniform_output() {};

private:
    SHIMMER_MEMBER ( uniform_output, GLint, location );
};
}

#endif
