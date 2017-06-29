#ifndef SHIMMER_VIDEO_OPENGL_GL_MATERIAL_MANAGER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_MATERIAL_MANAGER_HPP

#include "gl_material.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace shimmer
{
class gl_material_manager
{
public:
    std::shared_ptr<gl_material> get(const std::shared_ptr<material>& material);
private:
    std::unordered_map<std::string, std::shared_ptr<gl_material>> _materials;
};
}

#endif
