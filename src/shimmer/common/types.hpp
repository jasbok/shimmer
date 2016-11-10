#ifndef SHIMMER_COMMON_TYPES_H
#define SHIMMER_COMMON_TYPES_H

namespace shimmer
{

template<typename T = unsigned int>
class dimensions
{
public:
        T w, h;
};

template<typename T = int>
class coordinates
{
public:
        T x, y;
};

}

#endif
