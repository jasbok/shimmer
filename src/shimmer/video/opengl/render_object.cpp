#include "render_object.hpp"

shimmer::render_object::render_object()
{}

shimmer::render_object::render_object ( shimmer::model* model, shimmer::shader* shader, shimmer::texture* texture )
        : _model ( model ), _shader ( shader ), _texture ( texture )
{}

shimmer::render_object::~render_object()
{}

void shimmer::render_object::render()
{
        if(!_shader){
                //std::cout << "Error: shader not set for render object." << std::endl;
                return;
        }
        if(!_texture){
                //std::cout << "Error: texture not set for render object." << std::endl;
                return;
        }
        if(!_model){
                //std::cout << "Error: model not set for render object." << std::endl;
                return ;
        }

        _shader->use_program();
        for ( auto output : _uniform_outputs ) output->process();
        _model->render();
        _shader->reset_program();
}
