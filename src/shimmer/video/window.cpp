#include "window.hpp"

shimmer::window::window()
{}

shimmer::window::~window()
{}

void shimmer::window::resize ( const dimensions<>& dims )
{
        _dims = dims;
}

void shimmer::window::dims ( const dimensions<>& dims )
{
        _dims = dims;
}

shimmer::dimensions<> shimmer::window::dims() const
{
        return _dims;
}
