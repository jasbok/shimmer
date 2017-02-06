#include "gl.hpp"

void glFramebuffer(GLenum target, GLuint framebuffer)
{
        SHIM_LOG();
        sym::glBindFramebuffer(target, framebuffer);
}

void glFramebufferEXT(GLenum target, GLuint framebuffer)
{
        SHIM_LOG();
        sym::glBindFramebufferEXT(target, framebuffer);
}
