#ifndef SHIMMER_VIDEO_VIDEO_HPP
#define SHIMMER_VIDEO_VIDEO_HPP

#include "../common/types.hpp"
#include <vector>

namespace shimmer
{
class video
{
public:
        virtual void source ( const dimensions<>& dims );
        virtual void target ( const dimensions<>& dims );
        virtual void setup ();
        virtual void update ();
        virtual void update ( const coordinates<>& coords, const dimensions<>& dims );
        virtual void update ( const rectangle<>& rect );
        virtual void update ( const std::vector<rectangle<>>& rects );
protected:
        video();
        virtual ~video();

private:
        dimensions<> _source_dims, _target_dims;
};
}

#endif
