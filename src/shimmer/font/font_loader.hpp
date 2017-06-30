#ifndef SHIMMER_FONT_FONT_LOADER_HPP
#define SHIMMER_FONT_FONT_LOADER_HPP

#include "font_face.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class font_loader
{
public:
    font_loader();

    font_loader ( font_loader&& move );

    virtual ~font_loader();

    void operator= ( font_loader&& move );

    std::shared_ptr<font_face> load (
        const std::string& font_path,
        unsigned int font_size );

private:
    font_loader ( const font_loader& copy );

    void operator= ( const font_loader& copy );

private:
    FT_Library _ft_library;
};
}

#endif
