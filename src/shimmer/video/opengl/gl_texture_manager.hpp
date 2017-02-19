#ifndef SHIMMER_VIDEO_OPENGL_GL_TEXTURE_MANAGER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_TEXTURE_MANAGER_HPP

#include "gl_texture.hpp"
#include <memory>
#include <unordered_map>

namespace shimmer
{
class gl_texture_manager
{
public:
        std::shared_ptr<gl_texture> get(const std::shared_ptr<texture>& texture);
private:
        std::unordered_map<std::string, std::shared_ptr<gl_texture>> _textures;
};
}

#endif
