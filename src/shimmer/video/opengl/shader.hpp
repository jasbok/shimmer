#ifndef SHIMMER_VIDEO_OPENGL_SHADER
#define SHIMMER_VIDEO_OPENGL_SHADER

#include "attribute.hpp"
#include "common/macros.hpp"
#include <GL/glew.h>
#include <unordered_map>

namespace shimmer
{
class shader
{
public:
        shader();
        virtual ~shader();

        void use_program() const;
        void reset_program() const;

        attribute attributes(const std::string& name) const;
        attribute uniforms(const std::string& name) const;
        bool has_attribute(const std::string& attr) const;
        bool has_uniform(const std::string& attr) const;
private:
        typedef std::unordered_map<std::string, std::unordered_map<std::string, attribute>> variable_map; 
        SHIMMER_MEMBER ( shader, GLuint, program );
        SHIMMER_MEMBER ( shader, variable_map, variables );
};
}

#endif
