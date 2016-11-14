#ifndef SHIMMER_COMMON_TYPES_HPP
#define SHIMMER_COMMON_TYPES_HPP

#include <iostream>

namespace shimmer
{

template<typename T = unsigned int>
class dimensions
{
public:
        T w, h;

        dimensions ()
                : w ( 0 ), h ( 0 )
        {}

        dimensions ( T w, T h )
                : w ( w ), h ( h )
        {}

        bool operator== ( const dimensions<T>& op )
        {
                return this->w == op.w && this->h == op.h;
        }

        friend std::ostream &operator<< ( std::ostream &os, const dimensions<T> &dims )
        {
                os << "( w = " << dims.w << ", h = " << dims.h << " )";
                return os;
        }
};

template<typename T = int>
class coordinates
{
public:
        T x, y;

        coordinates ()
                : x ( 0 ), y ( 0 )
        {}

        coordinates ( T x, T y )
                : x ( x ), y ( y )
        {}

        bool operator== ( const coordinates<T>& op )
        {
                return this->x == op.x && this->y == op.y;
        }

        friend std::ostream &operator<< ( std::ostream &os, const coordinates<T> &coords )
        {
                os << "( x = " << coords.x << ", y = " << coords.y << " )";
                return os;
        }
};

template<typename C = coordinates<>, typename D = dimensions<>>
class rectangle
{
public:
        C coords;
        D dims;

        rectangle ()
                : coords(), dims()
        {}

        rectangle ( C coords, D dims )
                : coords ( coords ), dims ( dims )
        {}

        bool operator== ( const rectangle<C,D>& op )
        {
                return this->coords == op.coords && this->dims == op.dims;
        }

        friend std::ostream &operator<< ( std::ostream &os, const rectangle<C,D> &rect )
        {
                os << "[ coords = " << rect.coords << ", dims = " << rect.dims << " ]";
                return os;
        }
};

template<typename T = std::string>
class variable
{
public:
        T type;
        int size;
        std::string name;

        variable() {}

        variable ( T type,
                   int size,
                   const std::string& name )
                : type ( type ), size ( size ), name ( name )
        {}

        variable ( const variable& copy )
                : type ( copy.type ), size ( copy.size ), name ( copy.name )
        {}

        variable ( variable&& move )
                : type ( std::move ( move.type ) ), size ( move.size ), name ( std::move ( move.name ) )
        {}

        void operator= ( const variable& copy )
        {
                type = copy.type;
                size = copy.size;
                name = copy.name;
        }

        void operator= ( variable&& move )
        {
                type = std::move ( move.type );
                size = move.size;
                name = std::move ( move.name );
        }

        friend std::ostream &operator<< ( std::ostream &os, const variable& var )
        {
                os << "[ type = " << var.type << ", name = " << var.name << ", size = " << var.size << " ]";
                return os;
        }
};

}

#endif
