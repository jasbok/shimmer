#include "gl_uniform.hpp"

namespace shimmer
{

gl_uniform::gl_uniform(const uniform &uniform)
{
        _extend(uniform);
}

gl_uniform::~gl_uniform()
{}

uniform &gl_uniform::value(const std::__cxx11::string &value)
{
        uniform::value(value);
        _parse(value);
        return *this;
}

uniform &gl_uniform::value(std::__cxx11::string &&value)
{
        uniform::value(value);
        _parse(value);
        return *this;
}

void gl_uniform::_parse(const std::string& str)
{}

void gl_uniform::_extend(const uniform &uniform)
{
        name(uniform.name());
        type(uniform.type());
        value(uniform.value());
}

}
