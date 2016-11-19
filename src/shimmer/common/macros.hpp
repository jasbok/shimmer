#ifndef SHIMMER_MACROS
#define SHIMMER_MACROS

#define SHIMMER_MEMBER(CLASS, TYPE, NAME)                                                       \
                public: CLASS& NAME (const TYPE& NAME){ _##NAME = NAME; return *this; }         \
                        CLASS& NAME (TYPE&& NAME){ _##NAME = NAME; return *this; }              \
                        const TYPE NAME() const { return _##NAME; }                             \
                        TYPE NAME() { return _##NAME; }                                         \
                private: TYPE _##NAME

#define SHIMMER_PTR_MEMBER(CLASS, TYPE, NAME)                                                   \
                public: CLASS& NAME (TYPE&& NAME){ _##NAME = NAME; return *this; }              \
                        TYPE NAME() { return _##NAME; }                                         \
                private: TYPE _##NAME

#define SHIMMER_GETTER(CLASS, TYPE, NAME)                                                       \
                public: const TYPE NAME() const { return _##NAME; }                             \
                        TYPE NAME() { return _##NAME; }                                         \
                private: TYPE _##NAME

#define SHIMMER_SETTER(CLASS, TYPE, NAME)                                                       \
                public: CLASS& NAME (const TYPE& NAME){ _##NAME = NAME; return *this; }         \
                        CLASS& NAME (TYPE&& NAME){ _##NAME = NAME; return *this; }              \
                private: TYPE _##NAME

#endif
