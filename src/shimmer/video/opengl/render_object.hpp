#ifndef SHIMMER_VIDEO_OPENGL_RENDER_OBJECT
#define SHIMMER_VIDEO_OPENGL_RENDER_OBJECT

#include "model.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "common/macros.hpp"
#include "uniforms/uniform_output.hpp"
#include <memory>

namespace shimmer
{
class render_object
{
public:
        render_object();

        render_object (
            std::shared_ptr<model> model,
            std::shared_ptr<shader> shader);

        virtual ~render_object() {}

        void render();

private:
        SHIMMER_MEMBER (
            render_object,
            std::shared_ptr<class model>,
            render_model );

        SHIMMER_MEMBER (
            render_object,
            std::shared_ptr<class shader>,
            render_shader );
};
}

#endif

