#ifndef SHIMMER_VIDEO_VIDEO_HPP
#define SHIMMER_VIDEO_VIDEO_HPP

#include "../common/types.hpp"

namespace shimmer
{
class video
{
public:
        void source(const dimensions<>& dims);
        void setup(const dimensions<>& dims);
        void update();
        void update ( const coordinates<>& coords, const dimensions<>& dims );
protected:
        video();
        virtual ~video();
};
}

#endif
