#ifndef SHIMMER_VIDEO_COMMON_RESOURCE_MANAGER_HPP
#define SHIMMER_VIDEO_COMMON_RESOURCE_MANAGER_HPP

#include "fbo.hpp"
#include "font.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <string>
#include <unordered_map>

namespace shimmer
{
class resource_manager
{
public:
        virtual ~resource_manager() {}

        virtual std::shared_ptr<shimmer::fbo> get ( const std::shared_ptr<shimmer::fbo>& fbo ) = 0;
        virtual std::shared_ptr<shimmer::font> get ( const std::shared_ptr<shimmer::font>& font ) = 0;
        virtual std::shared_ptr<shimmer::material> get ( const std::shared_ptr<shimmer::material>& material ) = 0;
        virtual std::shared_ptr<shimmer::mesh> get ( const std::shared_ptr<shimmer::mesh>& mesh ) = 0;
        virtual std::shared_ptr<shimmer::model> get ( const std::shared_ptr<shimmer::model>& model ) = 0;
        virtual std::shared_ptr<shimmer::shader> get ( const std::shared_ptr<shimmer::shader>& shader ) = 0;
        virtual std::shared_ptr<shimmer::texture> get ( const std::shared_ptr<shimmer::texture>& texture ) = 0;
        
        virtual std::shared_ptr<shimmer::fbo> get_fbo ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::font> get_font ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::material> get_material ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::mesh> get_mesh ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::model> get_model ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::shader> get_shader ( const std::string& id ) = 0;
        virtual std::shared_ptr<shimmer::texture> get_texture ( const std::string& id ) = 0;
};
}

#endif





