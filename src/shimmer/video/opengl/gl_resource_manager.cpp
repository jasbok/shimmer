#include "gl_resource_manager.hpp"
#include "gl_shader.hpp"

shimmer::gl_resource_manager::gl_resource_manager()
{
}

shimmer::gl_resource_manager::~gl_resource_manager()
{
}

std::shared_ptr<shimmer::fbo> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::fbo>& fbo)
{
        return std::make_shared<shimmer::fbo>();
}

std::shared_ptr<shimmer::font> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::font>& font)
{
        return std::make_shared<shimmer::font>();
}

std::shared_ptr<shimmer::material> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::material>& material)
{
        return std::make_shared<shimmer::material>();
}

std::shared_ptr<shimmer::mesh> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::mesh>& mesh)
{
        return std::make_shared<shimmer::mesh>();
}

std::shared_ptr<shimmer::model> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::model>& model)
{
        return std::make_shared<shimmer::model>();
}

std::shared_ptr<shimmer::shader> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::shader>& shader)
{
        return _shader_manager.get(shader);
}

std::shared_ptr<shimmer::texture> shimmer::gl_resource_manager::get(const std::shared_ptr<shimmer::texture>& texture)
{
        return std::make_shared<shimmer::texture>();
}
