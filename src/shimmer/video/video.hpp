#ifndef SHIMMER_VIDEO_VIDEO_HPP
#define SHIMMER_VIDEO_VIDEO_HPP

#include "../common/types.hpp"

namespace shimmer
{
class video
{
public:
        virtual void source ( const dimensions<>& dims );
        virtual void target ( const dimensions<>& dims );
        virtual void setup ( const dimensions<>& dims );
        virtual void update();
        virtual void update ( const coordinates<>& coords, const dimensions<>& dims );
protected:
        video();
        virtual ~video();

private:
        dimensions<> _source_dims, _target_dims;
};
}

#endif
