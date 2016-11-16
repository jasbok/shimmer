#ifndef SHIMMER_VIDEO_OPENGL_SHADER
#define SHIMMER_VIDEO_OPENGL_SHADER

#include "glsl_variable.hpp"
#include "common/macros.hpp"
#include <GL/glew.h>
#include <unordered_map>
#include <vector>

namespace shimmer
{
class shader
{
public:
        shader ( GLuint program );
        virtual ~shader();

        void use_program() const;
        void reset_program() const;

        glsl_variable attributes ( const std::string& name ) const;
        glsl_variable uniforms ( const std::string& name ) const;
        bool has_attribute ( const std::string& attr ) const;
        bool has_uniform ( const std::string& attr ) const;
        shader& add ( const glsl_variable& var );
        shader& add ( const std::vector<glsl_variable>& variables );

        friend std::ostream &operator<< ( std::ostream &os, const shader& shader )
        {
                os << "[ program = " << shader.program()
                   << ", attributes = { ";
                for ( auto it : shader.attributes() ) {
                        os << it.second << ", ";
                }
                os << "}, uniforms = {";
                for ( auto it : shader.uniforms() ) {
                        os << it.second << ", ";
                }
                os << "} ]";
                return os;
        }
private:
        typedef std::unordered_map<std::string, glsl_variable> variable_map;
        SHIMMER_MEMBER ( shader, GLuint, program );
        SHIMMER_MEMBER ( shader, variable_map, attributes );
        SHIMMER_MEMBER ( shader, variable_map, uniforms );
};
}

#endif