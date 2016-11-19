#ifndef SHIMMER_VIDEO_OPENGL_UNIFORMS_TICKS_OUTPUT
#define SHIMMER_VIDEO_OPENGL_UNIFORMS_TICKS_OUTPUT

#include "uniform_output.hpp"

namespace shimmer
{
class ticks_output : public uniform_output
{
public:
        ticks_output(GLint location);
        virtual ~ticks_output();
        void process() override;
private:
};
}

#endif
