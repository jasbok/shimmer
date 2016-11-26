#ifndef SHIMMER_VIDEO_OPENGL_GLSL_VARIABLE
#define SHIMMER_VIDEO_OPENGL_GLSL_VARIABLE

#include "common/macros.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

namespace shimmer
{
class glsl_variable
{
public:
        enum class qualifier
        {
                UNKNOWN = 0, ATTRIBUTE, UNIFORM, VARYING
        };

        enum class type
        {
                UNKNOWN = 0,
                BOOL, INT, UINT, FLOAT, DOUBLE,
                BVEC2, BVEC3, BVEC4,
                IVEC2, IVEC3, IVEC4,
                UVEC2, UVEC3, UVEC4,
                VEC2,  VEC3,  VEC4,
                DVEC2, DVEC3, DVEC4,
                SAMPLER1D, ISAMPLER1D, USAMPLER1D,
                SAMPLER2D, ISAMPLER2D, USAMPLER2D,
                SAMPLER3D, ISAMPLER3D, USAMPLER3D,
                MAT2, MAT3, MAT4,
                MAT2X3, MAT3X2,
                MAT2X4, MAT4X2,
                MAT3X4, MAT4X3
        };

        glsl_variable();
        glsl_variable ( enum qualifier qualifier, enum type type, const std::string& name );
        glsl_variable ( enum qualifier qualifier, enum type type, unsigned int size, const std::string& name );
        virtual ~glsl_variable();

        static qualifier qualifier_from ( const std::string& str );
        static type type_from ( const std::string& str );
        static std::string str_from ( enum qualifier qualifier );
        static std::string str_from ( enum type type );

#define SHIMMER_GLSL_VARIABLE_VALUE(TYPE, GL_TYPE, GL_UNIFORM)          \
        void value(const GL_TYPE& val){                                 \
                if(_type == TYPE){                                      \
                        GL_UNIFORM(_location, val);                     \
                }                                                       \
        }
        SHIMMER_GLSL_VARIABLE_VALUE ( type::FLOAT, GLint, glUniform1i );
        SHIMMER_GLSL_VARIABLE_VALUE ( type::FLOAT, GLuint, glUniform1ui );
        SHIMMER_GLSL_VARIABLE_VALUE ( type::FLOAT, GLfloat, glUniform1f );

#define SHIMMER_GLSL_VARIABLE_VALUE_VEC(TYPE, GLM_TYPE, GL_UNIFORM)     \
        void value(const GLM_TYPE& val){                                \
                if(_type == TYPE){                                      \
                        GL_UNIFORM(_location, 1, glm::value_ptr(val));  \
                }                                                       \
        }
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::IVEC2, glm::ivec2, glUniform2iv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::IVEC3, glm::ivec3, glUniform3iv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::IVEC4, glm::ivec4, glUniform4iv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::UVEC2, glm::uvec2, glUniform2uiv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::UVEC3, glm::uvec3, glUniform3uiv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::UVEC4, glm::uvec4, glUniform4uiv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::VEC2, glm::vec2, glUniform2fv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::VEC3, glm::vec3, glUniform3fv );
        SHIMMER_GLSL_VARIABLE_VALUE_VEC ( type::VEC4, glm::vec4, glUniform4fv );

#define SHIMMER_GLSL_VARIABLE_VALUE_MAT(TYPE, GLM_TYPE, GL_UNIFORM)                     \
        void value(const GLM_TYPE& val){                                                \
                if(_type == TYPE){                                                      \
                        GL_UNIFORM(_location, 1, GL_FALSE, glm::value_ptr(val));        \
                }                                                                       \
        }
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT2, glm::mat2, glUniformMatrix2fv );
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT3, glm::mat3, glUniformMatrix3fv );
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT4, glm::mat4, glUniformMatrix4fv );

        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT2X3, glm::mat2x3, glUniformMatrix2x3fv );
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT2X3, glm::mat3x2, glUniformMatrix2x3fv );

        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT2X4, glm::mat2x4, glUniformMatrix2x4fv );
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT4X2, glm::mat4x2, glUniformMatrix4x2fv );

        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT3X4, glm::mat3x4, glUniformMatrix3x4fv );
        SHIMMER_GLSL_VARIABLE_VALUE_MAT ( type::MAT4X3, glm::mat4x3, glUniformMatrix4x3fv );


        friend std::ostream &operator<< ( std::ostream &os, const glsl_variable& var )
        {
                os << "[ qualifier = " << str_from ( var._qualifier )
                   << ", type = " << str_from ( var._type )
                   << ", size = " << var._size
                   << ", name = " << var._name
                   << ", location = " << var._location << " ]";
                return os;
        }
private:
        SHIMMER_MEMBER ( glsl_variable, enum qualifier, qualifier );
        SHIMMER_MEMBER ( glsl_variable, enum type, type );
        SHIMMER_MEMBER ( glsl_variable, unsigned int, size );
        SHIMMER_MEMBER ( glsl_variable, std::string, name );
        SHIMMER_MEMBER ( glsl_variable, GLint, location );

        static const std::unordered_map<std::string, enum type> _type_from_str_map;
};
}

#endif
