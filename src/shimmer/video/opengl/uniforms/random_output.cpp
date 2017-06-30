#include "random_output.hpp"
#include <random>
#include <ctime>

namespace shimmer
{
random_output::random_output ( GLint location, unsigned int count )
    : _count ( count ), _values ( new GLfloat[_count] )
{
    uniform_output::location ( location );
    srand ( time ( nullptr ) );
}

random_output::~random_output()
{
    delete [] _values;
}

void random_output::process()
{
    for ( unsigned int i = 0; i < _count; i++ ) {
        _values[i] = rand();
    }
    glUniform1fv ( uniform_output::location(), _count, _values );
}
}
