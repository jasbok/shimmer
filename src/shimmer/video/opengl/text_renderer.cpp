#include "text_renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

shimmer::text_renderer::text_renderer() :
        _scale ( 1.0 ),
        _colour ( {1.0, 1.0, 1.0, 1.0} ),
        _resolution ( {800, 600} ),
        _projection ( glm::ortho ( 0.0f, _resolution.w, 0.0f, _resolution.h ) )
{}

shimmer::text_renderer::~text_renderer()
{}

void shimmer::text_renderer::draw ( std::string text, const coordinates<GLfloat>& coords )
{
        _pen = {coords.x, _resolution.h - coords.y};
        glActiveTexture ( GL_TEXTURE0 );
        _shader->use_program();
        _quad.bind ( _shader );

        char prev = 0;
        for ( auto c : text ) {
                auto glyph = _font->glyph ( c );
                _pen.x += _font->kern ( prev, c ).x;
                glBindTexture ( GL_TEXTURE_2D, glyph.texture() );
                _quad.shape (
                        _pen.x,
                        _pen.y - ( ( int ) glyph.dims().h - glyph.bearing().y ),
                        glyph.dims().w * _scale,
                        glyph.dims().h * _scale );
                _quad.render();
                _pen.x += glyph.advance() * _scale;
        }
        glActiveTexture ( GL_TEXTURE0 );
}

shimmer::text_renderer & shimmer::text_renderer::shader ( const std::shared_ptr<class shader>& shader )
{
        _shader = shader;
        _shader->use_program()
        .set_uniform ( "colour", _colour )
        .set_uniform ( "projection", _projection );
        return *this;
}

shimmer::text_renderer & shimmer::text_renderer::colour ( const glm::vec4& colour )
{
        _colour = colour;
        _shader->use_program()
        .set_uniform ( "colour", _colour );
        return *this;
}

shimmer::text_renderer & shimmer::text_renderer::resolution ( const dimensions<GLfloat>& resolution )
{
        _resolution = resolution;
        _projection = glm::ortho ( 0.0f, _resolution.w, 0.0f, _resolution.h );
        _shader->use_program()
        .set_uniform ( "projection", _projection );
        return *this;
}
