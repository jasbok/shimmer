#include "video.hpp"

shimmer::video::video()
{}

shimmer::video::~video()
{}

void shimmer::video::source(const dimensions<>& dims)
{
        _source_dims = dims;
}

void shimmer::video::target(const dimensions<>& dims)
{
        _target_dims = dims;
}

void shimmer::video::setup(const dimensions<>& dims)
{
}

void shimmer::video::update()
{
}

void shimmer::video::update(const coordinates<>& coords, const dimensions<>& dims)
{
}
