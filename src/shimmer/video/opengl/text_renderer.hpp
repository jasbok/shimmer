#ifndef SHIMMER_VIDEO_OPENGL_TEXT_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_TEXT_RENDERER_HPP

#include "common/macros.hpp"
#include "common/types.hpp"
#include "fonts/gl_font.hpp"
#include "quad.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace shimmer
{
class text_renderer
{
public:
    text_renderer();

    virtual ~text_renderer() {}

    void draw ( std::string text, const coordinates<GLfloat>& coords );

    text_renderer& shader ( const std::shared_ptr<class shader>& shader );

    text_renderer& colour ( const glm::vec4& colour );

    text_renderer& resolution ( const dimensions<GLfloat>& resolution );

private:
    coordinates<GLfloat> _pen;

    quad _quad;

    SHIMMER_MEMBER ( text_renderer, std::shared_ptr<gl_font>, font );

    SHIMMER_GETTER ( text_renderer, std::shared_ptr<class shader>, shader );

    SHIMMER_MEMBER ( text_renderer, float, scale );

    SHIMMER_GETTER ( text_renderer, glm::vec4, colour );

    SHIMMER_GETTER ( text_renderer, dimensions<GLfloat>, resolution );

    SHIMMER_GETTER ( text_renderer, glm::mat4x4, projection );
};
}

#endif
