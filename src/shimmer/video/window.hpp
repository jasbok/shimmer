#ifndef SHIMMER_VIDEO_WINDOW_HPP
#define SHIMMER_VIDEO_WINDOW_HPP

#include "common/types.hpp"

namespace shimmer
{
class window
{
public:
        window();
        virtual ~window();

        dimensions<> resize ( const dimensions<>& dims );
        dimensions<> dims() const;
private:
        dimensions<> _dims;
};
}

#endif
