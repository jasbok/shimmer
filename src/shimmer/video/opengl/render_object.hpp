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
class render_object : public model
{
public:
        render_object();
        render_object ( model* model, shader* shader, texture* texture );
        virtual ~render_object();
        void render() override;
private:
        SHIMMER_MEMBER ( render_object, std::shared_ptr<class model>, model );
        SHIMMER_MEMBER ( render_object, std::shared_ptr<class shader>, shader );
        SHIMMER_MEMBER ( render_object, std::shared_ptr<class texture>, texture );
        SHIMMER_MEMBER ( render_object, std::vector<std::shared_ptr<uniform_output>>, uniform_outputs);
};
}

#endif

