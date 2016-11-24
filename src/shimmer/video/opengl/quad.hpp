#ifndef SHIMMER_VIDEO_OPENGL_QUAD_HPP
#define SHIMMER_VIDEO_OPENGL_QUAD_HPP

#include "model.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "common/types.hpp"
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

        void operator= ( quad&& move );

        void aspect_ratio ( const dimensions<GLfloat>& ratio );
        void shape ( const rectangle<coordinates<GLfloat>, dimensions<GLfloat>> rect );
        void render () override;
        void bind ( const std::shared_ptr<shader>& shader ) override;
private:
        GLuint _vbo;
        GLuint _vao;
private:
        quad ( const quad& copy ) = delete;
        void operator= ( const quad& copy ) = delete;
        void _buffer_data ( const std::vector<GLfloat>& data );
};
}

#endif
