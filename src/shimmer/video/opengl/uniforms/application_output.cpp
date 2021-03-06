#include "application_output.hpp"

namespace shimmer
{
application_output::application_output ( GLint location, GLuint texture )
    : _texture ( texture )
{
    uniform_output::location ( location );
}

void application_output::process()
{
    glActiveTexture ( GL_TEXTURE0 );
    glBindTexture ( GL_TEXTURE_2D, _texture );
    glUniform1i ( uniform_output::location(), 0 );
}

}
