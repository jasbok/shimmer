#ifndef SHIMMER_VIDEO_WINDOW_H
#define SHIMMER_VIDEO_WINDOW_H

#include "../common/types.hpp"

namespace shimmer
{
class window
{
public:
        virtual ~window();
protected:
        window();
        void dims ( const dimensions<>& dims );
        dimensions<> dims() const;
private:
        dimensions<> _dims;
};
}

#endif
