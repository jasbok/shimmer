#include "scene.hpp"

namespace shimmer
{
void scene::render()
{
        for(auto child : _children){
                child->render();
                for(auto model : _models){
                        model->render();
                }
        }
}
}


