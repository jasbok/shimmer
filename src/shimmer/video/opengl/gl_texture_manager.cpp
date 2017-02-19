#include "gl_texture_manager.hpp"
namespace shimmer
{

std::shared_ptr<gl_texture> gl_texture_manager::get(const std::shared_ptr<texture> &texture)
{
        if(texture->id().size() > 0) {
                if(!_textures[texture->id()]) {
                        _textures[texture->id()] = std::make_shared<gl_texture>(*texture);
                }
                return _textures[texture->id()];
        }
        return std::make_shared<gl_texture>(*texture);
}

}
