#ifndef OPENGL_HELPERS_H
#define OPENGL_HELPERS_H

#include <GL/glew.h>
#include <string>
#include <vector>

#define GL_LOG_SIZE 512

#define PRINT_GL_ERROR_ENUM(ENUM) printf("(%s:%u) GL Error: ENUM.\n", file, line)
#define PRINT_GL_ERROR() print_gl_error(__FILE__, __LINE__)

namespace shimmer
{
GLuint compile_shader ( const char* source, GLuint type );
GLuint compile_shader ( const std::string& source, GLuint type );
GLuint compile_shader ( const std::vector<std::string>& sources, GLuint type );

void link_program ( GLuint program, GLuint vs, GLuint fs );
void link_program ( GLuint program, const std::vector<GLuint> &vs_list, const std::vector<GLuint> &fs_list );
int print_gl_error ( const char* file, int line );
void detachShaders ( GLuint program, const std::vector<GLuint>& shaders );
void deleteShaders ( const std::vector<GLuint>& shaders );
}
#endif
