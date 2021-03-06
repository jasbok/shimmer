#include "shader_manager.hpp"
#include "opengl_helpers.hpp"
#include "common/file_helpers.hpp"
#include "common/regex_helpers.hpp"
#include "uniforms/application_output.hpp"
#include "uniforms/random_output.hpp"
#include "uniforms/ticks_output.hpp"

namespace shimmer
{

std::unordered_map<std::string, enum shimmer::shader_manager::shimmer_uniforms>
shimmer::shader_manager::_uniform_map = {
    {"shimmer_application", shimmer_uniforms::APPLICATION_OUTPUT},
    {"shimmer_random", shimmer_uniforms::RANDOM},
    {"shimmer_ticks", shimmer_uniforms::TICKS}
};

shader_manager::shader_manager ()
{}

std::shared_ptr<shader> shader_manager::create (
    const std::vector<std::string>& vs_in,
    const std::vector<std::string>& fs_in )
{
    auto vs_sources = _read_sources ( vs_in );
    auto fs_sources = _read_sources ( fs_in );
    auto vs_compiled = compile_shader ( vs_sources, GL_VERTEX_SHADER );
    auto fs_compiled = compile_shader ( fs_sources, GL_FRAGMENT_SHADER );
    auto program = _link_compiled ( {vs_compiled}, {fs_compiled} );
    auto variables = _read_variables ( {vs_sources, fs_sources}, program );
    auto uniform_outputs = _create_uniform_outputs ( variables );
    deleteShaders ( {{vs_compiled}, {fs_compiled}} );

    std::shared_ptr<shader> result = std::make_shared<shader> ( program );
    result->add ( variables );
    result->uniform_outputs ( uniform_outputs );
    return result;
}

std::vector<std::string> shader_manager::_read_sources (
    const std::vector<std::string>& paths )
{
    std::vector<std::string> sources;
    std::regex version_regex ( "\\s*#version\\s\\d{3}\\s*" );
    sources.push_back ( "#version 130\n" );

    for ( auto path : paths ) {
        std::string source = std::regex_replace (
                                 read_contents ( path ),
                                 version_regex ,
                                 "" );

        if ( !source.empty() ) {
            std::regex include_regex (
                "\\s*\\/{2}\\s*#include\\s+([\\w.\\/\\\\]*)\\s*" );

            for ( auto include : find_all ( source, include_regex, 1 ) ) {
                std::string include_source = read_contents ( include );

                sources.push_back ( std::regex_replace (
                                        include_source,
                                        version_regex ,
                                        "" ) );
            }
        }
        sources.push_back ( source );
    }

    return sources;
}

std::vector<std::string> shader_manager::_read_sources (
    const std::string& base,
    const std::vector<std::string>& paths )
{
    std::vector<std::string> full_paths;

    for ( auto path : paths ) {
        full_paths.push_back ( base + path );
    }

    return _read_sources ( paths );
}

std::vector<GLuint> shader_manager::_compile_sources (
    const std::vector<std::string>& sources,
    GLuint type )
{
    std::vector<GLuint> compiled_sources;

    for ( auto source : sources ) {
        compile_shader ( source, type );
    }

    return compiled_sources;
}

GLuint shader_manager::_link_compiled (
    const std::vector<GLuint>& vs,
    const std::vector<GLuint>& fs )
{
    GLuint program = 0;

    if ( !vs.empty() && !fs.empty() ) {
        program = glCreateProgram();
        link_program ( program, vs, fs );
        detachShaders ( program, {vs, fs} );
    } else {
        printf ( "==> Could not link vs and/or fs shader(s).\n" );
    }

    return program;
}

std::vector<glsl_variable> shader_manager::_read_variables (
    const std::vector<std::vector<std::string>>& sources_vec,
    GLuint program )
{
    // 0:qualifier 1:type 2:size 3:name
    std::regex regex (
        "\\s*(\\w+)\\s+(\\w+)\\s*(\\[(\\d)+\\])?\\s+([\\w]+).*?;" );

    std::vector<glsl_variable> results;

    for ( auto sources : sources_vec ) {
        for ( auto source : sources ) {
            for ( auto var : find_all ( source, regex, {1, 2, 4, 5} ) ) {
                auto variable = glsl_variable (
                                    glsl_variable::qualifier_from ( var[0] ),
                                    glsl_variable::type_from ( var[1] ),
                                    var[2].empty() ? 1 : std::stoi ( var[2] ),
                                    var[3] );

                if ( variable.qualifier()
                        == glsl_variable::qualifier::ATTRIBUTE ) {
                    variable.location ( glGetAttribLocation (
                                            program,
                                            variable.name().c_str() ) );
                } else if ( variable.qualifier()
                            == glsl_variable::qualifier::UNIFORM ) {
                    variable.location ( glGetUniformLocation (
                                            program,
                                            variable.name().c_str() ) );
                }

                results.push_back ( variable );
            }
        }
    }

    return results;
}

std::shared_ptr<uniform_output> shader_manager::_uniform_output_from (
    const glsl_variable& variable )
{
    std::shared_ptr<uniform_output> result = nullptr;

    if ( _uniform_map.find ( variable.name() ) != _uniform_map.end() ) {
        switch ( _uniform_map[variable.name()] ) {
        case shimmer_uniforms::APPLICATION_OUTPUT:
            if ( variable.type() == glsl_variable::type::SAMPLER2D ) {
                if ( _application_texture ) {
                    result = std::make_shared<application_output> (
                                 variable.location(),
                                 _application_texture->gl_texture() );
                }
            }
            break;

        case shimmer_uniforms::RANDOM:
            if ( variable.type() == glsl_variable::type::FLOAT ) {
                result = std::make_shared<random_output> (
                             variable.location(),
                             variable.size() );
            }
            break;

        case shimmer_uniforms::TICKS:
            if ( variable.type() == glsl_variable::type::UINT ) {
                result = std::make_shared<ticks_output> ( variable.location() );
            }
            break;
        }
    }

    return result;
}

std::vector<std::shared_ptr<uniform_output> >
shader_manager::_create_uniform_outputs (
    const std::vector<glsl_variable>& uniforms )
{
    std::vector<std::shared_ptr<uniform_output>> results;

    for ( auto uniform : uniforms ) {
        if ( uniform.qualifier() == glsl_variable::qualifier::UNIFORM ) {
            auto output = _uniform_output_from ( uniform );
            if ( output ) {
                results.push_back ( output );
            }
        }
    }

    return results;
}
}


