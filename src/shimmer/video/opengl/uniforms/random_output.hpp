#ifndef SHIMMER_VIDEO_OPENGL_UNIFORMS_RANDOM_OUTPUT
#define SHIMMER_VIDEO_OPENGL_UNIFORMS_RANDOM_OUTPUT

#include "uniform_output.hpp"
#include <GL/glew.h>
#include <vector>

namespace shimmer
{
class random_output : public uniform_output
{
public:
    random_output ( GLint location, unsigned int count );

    virtual ~random_output();

    void process() override;

private:
    unsigned int _count;

    GLfloat* _values;
};
}

#endif
