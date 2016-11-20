#ifndef SHIMMER_VIDEO_OPENGL_MODEL
#define SHIMMER_VIDEO_OPENGL_MODEL

#include "shader.hpp"
#include <memory>

namespace shimmer{
        class model{
        public:
                virtual ~model(){}
                virtual void render() = 0;
                virtual void bind(const std::shared_ptr<shader>& shader) = 0;
        };
}

#endif
