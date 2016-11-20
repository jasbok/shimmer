#include "render_object.hpp"

shimmer::render_object::render_object()
{}

shimmer::render_object::render_object ( std::shared_ptr<shimmer::model> model, std::shared_ptr<shimmer::shader> shader )
        : _render_model ( model ), _render_shader ( shader )
{
        _render_model->bind(_render_shader);
}

shimmer::render_object::~render_object()
{}

void shimmer::render_object::render()
{
        if(!_render_shader){
                std::cout << "Error: shader not set for render object." << std::endl;
                return;
        }
        if(!_render_model){
                std::cout << "Error: model not set for render object." << std::endl;
                return ;
        }

        _render_shader->use_program();
        _render_model->render();
        _render_shader->reset_program();
}
