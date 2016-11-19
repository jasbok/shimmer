#ifndef SHIMMER_VIDEO_OPENGL_QUAD_HPP
#define SHIMMER_VIDEO_OPENGL_QUAD_HPP

#include "model.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "../../common/types.hpp"
#include <GL/glew.h>
#include <memory>

namespace shimmer
{
class quad : public model
{
public:
        quad ();
        quad ( const dimensions<GLfloat>& ratio );
        quad ( quad&& quad );
        virtual ~quad();

        void operator=(quad&& move);

        void aspect_ratio ( const dimensions<GLfloat>& ratio );
        void render () override;
        void bind (std::shared_ptr<shader>& shader);
private:
        GLuint _vbo;
        GLuint _vao;

        void operator=(const quad& copy);
};
}

#endif
