#ifndef SHIMMER_VIDEO_OPENGL_GLSL_VARIABLE
#define SHIMMER_VIDEO_OPENGL_GLSL_VARIABLE

#include "common/macros.hpp"
#include <GL/glew.h>
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
                SAMPLER3D, ISAMPLER3D, USAMPLER3D
        };

        glsl_variable();
        glsl_variable ( enum qualifier qualifier, enum type type, const std::string& name );
        glsl_variable ( enum qualifier qualifier, enum type type, unsigned int size, const std::string& name );
        virtual ~glsl_variable();

        static qualifier qualifier_from ( const std::string& str );
        static type type_from ( const std::string& str );
        static std::string str_from ( enum qualifier qualifier );
        static std::string str_from ( enum type type );

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
