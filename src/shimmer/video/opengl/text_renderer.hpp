#ifndef SHIMMER_VIDEO_OPENGL_TEXT_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_TEXT_RENDERER_HPP

#include "common/macros.hpp"
#include "fonts/gl_font.hpp"
#include "quad.hpp"
#include "shader.hpp"
#include <memory>

namespace shimmer
{
class text_renderer
{
public:
        void draw(std::string text, const coordinates<GLfloat>& coords, float scale);
private:
        coordinates<GLfloat> _pen;
        quad _quad;
        SHIMMER_MEMBER(text_renderer, std::shared_ptr<gl_font>, font);
        SHIMMER_MEMBER(text_renderer, std::shared_ptr<shader>, shader);

        _shape_quad(const gl_glyph& glyph, float scale);
        _draw_glyph();
};
}

#endif
