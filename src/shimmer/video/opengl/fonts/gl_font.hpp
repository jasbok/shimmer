#ifndef SHIMMER_VIDEO_OPENGL_FONTS_GL_FONT_HPP
#define SHIMMER_VIDEO_OPENGL_FONTS_GL_FONT_HPP

#include "font/font_loader.hpp"

namespace shimmer{
        class gl_font{
        public:
                gl_font(font_face&& face);
                virtual ~gl_font();
        private:
                font_face _face;
        };
}

#endif
