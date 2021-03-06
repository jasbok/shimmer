#include "render_object.hpp"

namespace shimmer
{
render_object::render_object()
{}

render_object::render_object (
    std::shared_ptr<model> model,
    std::shared_ptr<shader> shader )
    : _render_model ( model ), _render_shader ( shader )
{
    _render_model->bind ( _render_shader );
}

void render_object::render()
{
    if ( !_render_shader ) {
        std::cout << "Error: shader not set for render object." << std::endl;
        return;
    }
    if ( !_render_model ) {
        std::cout << "Error: model not set for render object." << std::endl;
        return ;
    }

    print_gl_error ( __FILE__, __LINE__ );
    _render_shader->use_program();
    print_gl_error ( __FILE__, __LINE__ );
    _render_model->render();
    print_gl_error ( __FILE__, __LINE__ );
    _render_shader->reset_program();
    print_gl_error ( __FILE__, __LINE__ );
}
}
