#ifndef OPENGL_HELPERS_HPP
#define OPENGL_HELPERS_HPP

#include "glsl_variable.hpp"
#include "common/types.hpp"
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#define PRINT_GL_ERROR_ENUM(ENUM) printf("(%s:%u) GL Error: ENUM.\n", file, line)
#define PRINT_GL_ERROR() print_gl_error(__FILE__, __LINE__)

namespace shimmer
{
GLuint compile_shader ( const char* source, GLuint type );
GLuint compile_shader ( const std::string& source, GLuint type );
GLuint compile_shader ( const std::vector<std::string>& sources, GLuint type );

void link_program ( GLuint program, GLuint vs, GLuint fs );
void link_program ( GLuint program, const std::vector<GLuint> &vs_list, const std::vector<GLuint> &fs_list );
void detachShaders ( GLuint program, const std::vector<std::vector<GLuint>>& shaders_vec );
void deleteShaders ( const std::vector<std::vector<GLuint>>& shaders_vec );

int print_gl_error ( const char* file, int line );
}
#endif
