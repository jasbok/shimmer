#ifndef SHIMMER_VIDEO_OPENGL_SHADER
#define SHIMMER_VIDEO_OPENGL_SHADER

#include "attribute.hpp"
#include "common/macros.hpp"
#include <GL/glew.h>
#include <vector>

namespace shimmer
{
class shader
{
public:
        shader();
        virtual ~shader();

        void use_program() const;
        void reset_program() const;
private:
        SHIMMER_MEMBER ( shader, GLuint, program );
        SHIMMER_MEMBER ( shader, std::vector<attribute>, attributes );
        SHIMMER_MEMBER ( shader, std::vector<attribute>, uniforms );
};
}

#endif
