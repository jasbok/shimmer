#include "gl_shader_manager.hpp"
#include "gl_program.hpp"
#include "gl_shader.hpp"
#include "common/file_utils.hpp"
#include "common/regex_helpers.hpp"
#include <iostream>

shimmer::gl_shader_manager::gl_shader_manager()
{}

shimmer::gl_shader_manager::~gl_shader_manager()
{}

std::shared_ptr<shimmer::gl_program> shimmer::gl_shader_manager::get ( const std::shared_ptr<shimmer::shader>& shader )
{
        auto vs = _get_gl_shaders ( shader->vertex_shaders(), GL_VERTEX_SHADER );
        auto fs = _get_gl_shaders ( shader->fragment_shaders(), GL_FRAGMENT_SHADER );
        auto key = _get_hash ( {vs, fs} );
        if ( !_gl_programs[key] ) {
                _gl_programs[key] = std::make_shared<shimmer::gl_program> ( *shader, std::move(vs), std::move(fs) );
        }
        return _gl_programs[key];
}

std::size_t shimmer::gl_shader_manager::_get_hash ( const std::vector<std::vector<std::shared_ptr<gl_shader> > >& pointers )
{
        std::size_t h;
        for ( auto y : pointers ) {
                for ( auto x : y ) {
                        h = std::hash<std::shared_ptr<gl_shader>> {} ( x ) ^ ( h << 1 );
                }
        }
        return h;
}

std::vector<std::shared_ptr<shimmer::gl_shader>> shimmer::gl_shader_manager::_get_gl_shaders ( const std::vector<std::string>& paths, GLuint type )
{
        std::vector<std::shared_ptr<gl_shader>> shaders;
        for ( auto path : paths ) {
                if ( !_gl_shaders[path] ) {
                        std::vector<std::string> sources = {file_utils::read_contents ( path )};
                        _gl_shaders[path] = std::make_shared<gl_shader> (std::move(sources), type);
                }
                shaders.push_back ( _gl_shaders[path] );
        }
        return shaders;
}
