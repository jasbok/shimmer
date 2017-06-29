#ifndef SHIMMER_VIDEO_OPENGL_GL_RESOURCE_MANAGER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_RESOURCE_MANAGER_HPP

#include "video/common/resource_manager.hpp"
#include "gl_shader_manager.hpp"
#include "gl_texture_manager.hpp"

namespace shimmer
{
class gl_resource_manager : public resource_manager
{
public:
        gl_resource_manager();
        virtual ~gl_resource_manager();

        std::shared_ptr<shimmer::fbo> get ( const std::shared_ptr<shimmer::fbo> & fbo ) override;
        std::shared_ptr<shimmer::font> get ( const std::shared_ptr<shimmer::font> & font ) override;
        std::shared_ptr<shimmer::material> get ( const std::shared_ptr<shimmer::material> & material ) override;
        std::shared_ptr<shimmer::mesh> get ( const std::shared_ptr<shimmer::mesh> & mesh ) override;
        std::shared_ptr<shimmer::model> get ( const std::shared_ptr<shimmer::model> & model ) override;
        std::shared_ptr<shimmer::shader> get ( const std::shared_ptr<shimmer::shader> & shader ) override;
        std::shared_ptr<shimmer::texture> get ( const std::shared_ptr<shimmer::texture> & texture ) override;

        std::shared_ptr<shimmer::fbo> get_fbo ( const std::string& id ) override;
        std::shared_ptr<shimmer::font> get_font ( const std::string& id ) override;
        std::shared_ptr<shimmer::material> get_material ( const std::string& id ) override;
        std::shared_ptr<shimmer::mesh> get_mesh ( const std::string& id ) override;
        std::shared_ptr<shimmer::model> get_model ( const std::string& id ) override;
        std::shared_ptr<shimmer::shader> get_shader ( const std::string& id ) override;
        std::shared_ptr<shimmer::texture> get_texture ( const std::string& id ) override;

private:
        gl_shader_manager _shader_manager;
        gl_texture_manager _texture_manager;
};
}

#endif
