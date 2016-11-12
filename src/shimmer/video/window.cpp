#include "window.hpp"

shimmer::window::window()
{}

shimmer::window::~window()
{}

void shimmer::window::resize ( const dimensions<>& dims )
{
        _dims.w = dims.w < 50 ? 50 : dims.w > 1920 ? 1920 : dims.w;
        _dims.h = dims.h < 50 ? 50 : dims.h > 1080 ? 1080 : dims.h;
}

void shimmer::window::dims ( const dimensions<>& dims )
{
        _dims = dims;
}

shimmer::dimensions<> shimmer::window::dims() const
{
        return _dims;
}