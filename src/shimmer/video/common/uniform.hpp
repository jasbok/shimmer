#ifndef SHIMMER_VIDEO_COMMON_UNIFORM_HPP
#define SHIMMER_VIDEO_COMMON_UNIFORM_HPP

#include "common/macros.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class uniform
{
public:
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

        uniform() {}

        uniform ( const enum type& type, const std::string& name )
                : _type ( type ), _name ( name )
        {}

        uniform ( const enum type& type, std::string&& name )
                : _type ( type ), _name ( name )
        {}

        virtual ~uniform() {}

        virtual void set() {};

private:
        SHIMMER_MEMBER ( uniform, std::string, id );
        SHIMMER_MEMBER ( uniform, enum type, type );
        SHIMMER_MEMBER ( uniform, std::string, name );
        SHIMMER_MEMBER ( uniform, std::string, value );
};
}

#endif
