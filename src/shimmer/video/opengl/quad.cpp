#include "quad.hpp"

shimmer::quad::quad()
{
        glGenBuffers ( 1, &_vbo );
        glGenVertexArrays ( 1, &_vao );
        shape ( {1.0, 1.0} );
}

shimmer::quad::quad ( const dimensions<GLfloat>& ratio )
{
        glGenBuffers ( 1, &_vbo );
        glGenVertexArrays ( 1, &_vao );
        shape ( ratio );
}

shimmer::quad::~quad()
{
        glDeleteBuffers ( 1, &_vbo );
        glDeleteVertexArrays ( 1, &_vao );
}

void shimmer::quad::shape ( const dimensions<GLfloat>& ratio )
{
        GLfloat screen_vertices[] = {
                // Vertices               // Texcoord
                ratio.w,   ratio.h,   0.0,        1.0, 0.0,
                ratio.w,   -ratio.h,  0.0,        1.0, 1.0,
                -ratio.w,  -ratio.h,  0.0,        0.0, 1.0,
                -ratio.w,  ratio.h,   0.0,        0.0, 0.0
        };

        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        glBufferData ( GL_ARRAY_BUFFER, sizeof ( screen_vertices ), screen_vertices, GL_STATIC_DRAW );
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );

        glBindVertexArray ( _vao );
        glActiveTexture ( GL_TEXTURE0 );
        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
}

void shimmer::quad::render ( const shimmer::shader& shader )
{
        shader.use_program();
        glDrawArrays ( GL_QUADS, 0, 4 );
}
