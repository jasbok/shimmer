#ifndef SHIMMER_VIDEO_RENDERER_HPP
#define SHIMMER_VIDEO_RENDERER_HPP

namespace shimmer
{
class renderer
{
public:
        virtual ~renderer(){};
        virtual void pixels(void* pixels) = 0;
        virtual void render() = 0;
private:
};
}

#endif
