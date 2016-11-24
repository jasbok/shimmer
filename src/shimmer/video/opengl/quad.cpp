#include "quad.hpp"

shimmer::quad::quad()
{
        glGenBuffers ( 1, &_vbo );
        glGenVertexArrays ( 1, &_vao );
        aspect_ratio ( {1.0, 1.0} );
}

shimmer::quad::quad ( const dimensions<GLfloat>& ratio )
{
        glGenBuffers ( 1, &_vbo );
        glGenVertexArrays ( 1, &_vao );
        aspect_ratio ( ratio );
}

shimmer::quad::quad ( shimmer::quad&& move )
        : _vbo ( move._vbo ), _vao ( move._vao )
{
        move._vbo = 0;
        move._vao = 0;
}


shimmer::quad::~quad()
{
        glDeleteBuffers ( 1, &_vbo );
        glDeleteVertexArrays ( 1, &_vao );
}

void shimmer::quad::operator= ( shimmer::quad && move )
{
        this->_vbo = move._vbo;
        this->_vao = move._vao;
        move._vbo = 0;
        move._vao = 0;
}


void shimmer::quad::aspect_ratio ( const dimensions<GLfloat>& ratio )
{
        _buffer_data ( {
                // Position                             // Texcoord
                -ratio.w,  ratio.h,   0.0,              0.0, 0.0,       // Top Left
                ratio.w,   ratio.h,   0.0,              1.0, 0.0,       // Top Right
                ratio.w,   -ratio.h,  0.0,              1.0, 1.0,       // Bottom Right
                -ratio.w,  -ratio.h,  0.0,              0.0, 1.0        // Bottom Left
        } );
}

void shimmer::quad::shape ( const rectangle<coordinates<GLfloat>,dimensions<GLfloat>> rect )
{
        _buffer_data ( {
                // Position                                                                     // Texcoord
                rect.coords.x,                  rect.coords.y,                    0.0,          0.0, 0.0,       // Top Left
                rect.coords.x + rect.dims.w,    rect.coords.y,                    0.0,          1.0, 0.0,       // Top Right
                rect.coords.x + rect.dims.w,    rect.coords.y + rect.dims.h,      0.0,          1.0, 1.0,       // Bottom Right
                rect.coords.x,                  rect.coords.y + rect.dims.h,      0.0,          0.0, 1.0        // Bottom Left
        } );
}

void shimmer::quad::bind ( const std::shared_ptr<shader>& shader )
{
        glBindVertexArray ( _vao );
        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        if ( shader->has_attribute ( "position" ) ) {
                GLint position = shader->attributes ( "position" ).location();
                glVertexAttribPointer ( position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) 0 );
                glEnableVertexAttribArray ( position );
        } else {
                std::cerr << "No position attributes in vertex shader." << std::endl;
        }
        if ( shader->has_attribute ( "texcoord" ) ) {
                GLint texcoord = shader->attributes ( "texcoord" ).location();
                glEnableVertexAttribArray ( texcoord );
                glVertexAttribPointer ( texcoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) ( 3 * sizeof ( GLfloat ) ) );
        }
        glBindVertexArray ( 0 );
}

void shimmer::quad::render ()
{
        glBindVertexArray ( _vao );
        glDrawArrays ( GL_QUADS, 0, 4 );
        glBindVertexArray ( 0 );
}

void shimmer::quad::_buffer_data ( const std::vector<GLfloat>& data )
{
        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        glBufferData ( GL_ARRAY_BUFFER, data.size() * sizeof ( GLfloat ), &data[0], GL_STATIC_DRAW );
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}
