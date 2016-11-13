#include "opengl_renderer.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create()
{
        glewExperimental = true;
        glewInit();
        return new opengl_renderer();
}

shimmer::opengl_renderer::opengl_renderer()
{}

shimmer::opengl_renderer::~opengl_renderer()
{}

void shimmer::opengl_renderer::render()
{
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear ( GL_COLOR_BUFFER_BIT );
}

void shimmer::opengl_renderer::pixels(void* pixels)
{}
