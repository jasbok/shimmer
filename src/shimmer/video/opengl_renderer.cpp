#include "opengl_renderer.hpp"
#include "common/config.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create()
{
        glewExperimental = true;
        glewInit();
        return new opengl_renderer();
}

shimmer::opengl_renderer::opengl_renderer()
{
        _shader_manager.create_shader({config::instance().vertex_shader},{config::instance().fragment_shader});
}

shimmer::opengl_renderer::~opengl_renderer()
{}

void shimmer::opengl_renderer::render()
{
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear ( GL_COLOR_BUFFER_BIT );
        _foreground.render();
}

void shimmer::opengl_renderer::pixels(void* pixels)
{}
