#ifndef SHIMMER_VIDEO_WINDOW_HPP
#define SHIMMER_VIDEO_WINDOW_HPP

#include "../common/types.hpp"

namespace shimmer
{
class window
{
public:
        void resize ( const dimensions<>& dims );
protected:
        window();
        virtual ~window();

        void dims ( const dimensions<>& dims );
        dimensions<> dims() const;
private:
        dimensions<> _dims;
};
}

#endif
