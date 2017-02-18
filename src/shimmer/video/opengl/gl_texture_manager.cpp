#include "gl_texture_manager.hpp"
namespace shimmer{

std::shared_ptr<gl_texture> gl_texture_manager::get(const std::shared_ptr<texture> &texture)
{
        return std::shared_ptr<gl_texture>();
}

std::shared_ptr<gl_texture> gl_texture_manager::_create(const std::shared_ptr<texture> &texture)
{
        return std::shared_ptr<gl_texture>();
}

}
