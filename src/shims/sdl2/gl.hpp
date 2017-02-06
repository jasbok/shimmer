#ifndef SHIMS_SDL2_GL_HPP
#define SHIMS_SDL2_GL_HPP

#include "shim.hpp"
#include <GL/gl.h>

SHIM ( void, glBindFramebuffer,
       GLenum target,
       GLuint framebuffer );

SHIM ( void, glBindFramebufferEXT,
       GLenum target,
       GLuint framebuffer );

#endif
