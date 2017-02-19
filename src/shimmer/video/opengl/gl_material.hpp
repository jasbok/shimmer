#ifndef SHIMMER_VIDEO_OPENGL_GL_MATERIAL_HPP
#define SHIMMER_VIDEO_OPENGL_GL_MATERIAL_HPP

#include "video/common/material.hpp"

namespace shimmer
{
class gl_material : public material
{
public:
        gl_material(const material& mat);
        virtual ~gl_material();

        virtual void use();
private:
        void _extend(const material& mat);
};
}

#endif
