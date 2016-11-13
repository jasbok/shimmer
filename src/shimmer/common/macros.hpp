#ifndef SHIMMER_MACROS
#define SHIMMER_MACROS

#define SHIMMER_MEMBER(CLASS, TYPE, NAME) public: CLASS& NAME (const TYPE& NAME){ _##NAME = NAME; return *this; } TYPE NAME(){ return _##NAME; } private: TYPE _##NAME


#endif
