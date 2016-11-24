#include "text_renderer.hpp"

void shimmer::text_renderer::draw ( std::string text, const coordinates<GLfloat>& coords, float scale )
{
        _pen = coords;
        for ( auto c : text ) {
                auto glyph = _font->glyph ( c );
                _shape_quad ( glyph, scale );
        }
}

int shimmer::text_renderer::_shape_quad ( const shimmer::gl_glyph& glyph, float scale )
{
        _quad.shape ( { _pen,
                {
                        static_cast<GLfloat> ( glyph.dims().w * scale ),
                        static_cast<GLfloat> ( glyph.dims().h * scale )
                }
        } );
}

int shimmer::text_renderer::_draw_glyph()
{
        
}
