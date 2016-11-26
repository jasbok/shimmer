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

        dimensions ( const dimensions& copy )
                : w ( copy.w ), h ( copy.h )
        {}

        dimensions ( dimensions&& move )
                : w ( move.w ), h ( move.h )
        {}

        dimensions& operator= ( const dimensions& copy )
        {
                this->w = copy.w;
                this->h = copy.h;
                return *this;
        }

        dimensions& operator= ( dimensions&& move )
        {
                this->w = move.w;
                this->h = move.h;
                return *this;
        }

        bool operator== ( const dimensions<T>& op )
        {
                return this->w == op.w && this->h == op.h;
        }

        bool operator!= ( const dimensions<T>& op )
        {
                return this->w != op.w || this->h != op.h;
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

        coordinates ( const coordinates<T>& copy )
                : x ( copy.x ), y ( copy.y )
        {}

        coordinates ( coordinates<T>&& move )
                : x ( move.x ), y ( move.y )
        {}

        coordinates& operator= ( const coordinates& copy )
        {
                this->x = copy.x;
                this->y = copy.y;
                return *this;
        }

        coordinates& operator= ( coordinates&& move )
        {
                this->x = move.x;
                this->y = move.y;
                return *this;
        }

        bool operator== ( const coordinates<T>& op )
        {
                return this->x == op.x && this->y == op.y;
        }

        bool operator!= ( const coordinates<T>& op )
        {
                return this->x != op.x || this->y != op.y;
        }

        coordinates operator+ ( const coordinates<T>& op )
        {
                return {this->x + op.x, this->y + op->y};
        }

        coordinates operator- ( const coordinates<T>& op )
        {
                return {this->x - op.x, this->y - op->y};
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

        rectangle ( const C& coords, const D& dims )
                : coords ( coords ), dims ( dims )
        {}

        rectangle ( const rectangle<C,D>& copy )
                : coords ( copy.coords ), dims ( copy.dims )
        {}

        rectangle ( rectangle<C,D>&& move )
                : coords ( move.coords ), dims ( move.dims )
        {}

        bool operator== ( const rectangle<C,D>& copy )
        {
                return this->coords == copy.coords && this->dims == copy.dims;
        }

        bool operator== ( rectangle<C,D>&& move )
        {
                return this->coords == move.coords && this->dims == move.dims;
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

template<typename T = unsigned int>
class colour
{
public:
        T r, g, b, a;

        colour ()
                : r ( 0 ), g ( 0 ), b ( 0 ), a ( 0 )
        {}

        colour ( T r, T g, T b, T a )
                : r ( r ), g ( g ), b ( b ), a ( a )
        {}

        colour ( const colour& copy )
                : r ( copy.r ), g ( copy.g ), b ( copy.b ), a ( copy.a )
        {}

        colour ( colour&& move )
                : r ( move.r ), g ( move.g ), b ( move.b ), a ( move.a )
        {}

        colour& operator= ( const colour& copy )
        {
                this->r = copy.r;
                this->g = copy.g;
                this->b = copy.b;
                this->a = copy.a;
                return *this;
        }

        colour& operator= ( colour&& move )
        {
                this->r = move.r;
                this->g = move.g;
                this->b = move.b;
                this->a = move.a;
                return *this;
        }

        bool operator== ( const colour<T>& op )
        {
                return this->r == op.r && this->g == op.g && this->b == op.b && this->a == op.a;
        }

        bool operator!= ( const colour<T>& op )
        {
                return this->r != op.r || this->g != op.g || this->b != op.b || this->a != op.a;
        }

        friend std::ostream &operator<< ( std::ostream &os, const colour<T> &colour )
        {
                os << "( r = " << colour.r << ", g = " << colour.g << ", b = " << colour.b << ", a = " << colour.a << " )";
                return os;
        }
};

}

#endif
