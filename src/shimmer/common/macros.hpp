#ifndef SHIMMER_MACROS
#define SHIMMER_MACROS

#define SHIMMER_MEMBER(CLASS, TYPE, NAME)                                                       \
                public: CLASS& NAME (const TYPE& NAME){ _##NAME = NAME; return *this; }         \
                        CLASS& NAME (TYPE&& NAME){ _##NAME = NAME; return *this; }              \
                        const TYPE NAME() const { return _##NAME; }                             \
                        TYPE NAME() { return _##NAME; }                                         \
                private: TYPE _##NAME

#endif
