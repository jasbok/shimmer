#include "font_loader.hpp"
#include <iostream>

namespace shimmer
{
font_loader::font_loader()
{
    auto ft_error = FT_Init_FreeType ( &_ft_library );
    if ( ft_error ) {
        std::cerr << "Failed to initialise FreeType library: "
                  << freetype_string_from ( ft_error ) << "." << std::endl;
    }
}

font_loader::font_loader ( font_loader && move )
    : _ft_library ( move._ft_library )
{
    move._ft_library = nullptr;
}


font_loader::~font_loader()
{
    if ( _ft_library ) {
        FT_Done_FreeType ( _ft_library );
    }
}

void font_loader::operator= ( font_loader && move )
{
    this->_ft_library = move._ft_library;
    move._ft_library = nullptr;
}

std::shared_ptr<font_face> font_loader::load (
    const std::string& font_path,
    unsigned int font_size )
{
    FT_Face face;
    auto ft_error = FT_New_Face ( _ft_library, font_path.c_str(), 0, &face );

    if ( ft_error ) {
        std::cerr << "Failed to load font face (" << font_path << "): "
                  << freetype_string_from ( ft_error ) << "." << std::endl;
        return nullptr;
    }

    return std::make_shared<font_face> ( face, font_size );
}

}
