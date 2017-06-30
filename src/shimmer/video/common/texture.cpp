#include "texture.hpp"

namespace shimmer
{

texture::texture() {}

texture::texture ( const std::string& id )
    : _id ( id ) {}

texture::texture ( std::string&& id )
    : _id ( id ) {}

texture::texture ( unsigned int width, unsigned int height )
    : _width ( width ),
      _height ( height )
{}

texture::texture (
    const std::string& id,
    unsigned int width,
    unsigned int height )
    : _id ( id ),
      _width ( width ),
      _height ( height )
{}

texture::texture (
    std::string&& id,
    unsigned int width,
    unsigned int height )
    : _id ( id ),
      _width ( width ),
      _height ( height )
{}

}
