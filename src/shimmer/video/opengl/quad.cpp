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
                // Position                             // Texcoord
                ratio.w,   ratio.h,   0.0,              1.0, 0.0,
                ratio.w,   -ratio.h,  0.0,              1.0, 1.0,
                -ratio.w,  -ratio.h,  0.0,              0.0, 1.0,
                -ratio.w,  ratio.h,   0.0,              0.0, 0.0
        };

        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        glBufferData ( GL_ARRAY_BUFFER, sizeof ( screen_vertices ), screen_vertices, GL_STATIC_DRAW );
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}

void shimmer::quad::bind ( const shimmer::shader* shader )
{
        _shader = shader;
        _setup_vertex_attribs();
}

void shimmer::quad::render ()
{
        glBindVertexArray ( _vao );
        glDrawArrays ( GL_QUADS, 0, 4 );
        glBindVertexArray ( 0 );
}

void shimmer::quad::_setup_vertex_attribs()
{
        if ( _shader->has_attribute ( "position" ) && _shader->has_attribute ( "texcoord" ) ) {
                GLint position = _shader->attributes ( "position" ).location();
                GLint texcoord = _shader->attributes ( "texcoord" ).location();
                glBindVertexArray ( _vao );
                glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
                glVertexAttribPointer ( position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) 0 );
                glVertexAttribPointer ( texcoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) ( 3 * sizeof ( GLfloat ) ) );
                glEnableVertexAttribArray ( position );
                glEnableVertexAttribArray ( texcoord );
                glBindVertexArray ( 0 );
        } else {
                std::cerr << "Expected position and/or texcoord attributes in vertex shader." << std::endl;
        }
}
