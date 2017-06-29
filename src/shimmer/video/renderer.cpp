#include "renderer.hpp"

namespace shimmer
{
void renderer::render ( std::shared_ptr<scene> scene )
{
        scene->render();
}
}
