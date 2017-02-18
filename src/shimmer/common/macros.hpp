#ifndef SHIMMER_MACROS
#define SHIMMER_MACROS

#define SHIMMER_MEMBER(CLASS, TYPE, NAME)								\
		public: virtual CLASS& NAME (const TYPE& NAME){ _##NAME = NAME; return *this; }         \
			virtual CLASS& NAME (TYPE&& NAME){ _##NAME = NAME; return *this; }              \
			virtual const TYPE NAME() const { return _##NAME; }                             \
			virtual TYPE NAME() { return _##NAME; }                                         \
		private: TYPE _##NAME

#define SHIMMER_VOID_MEMBER(CLASS, NAME)                                                                \
		public: CLASS& NAME (std::shared_ptr<void> NAME){ _##NAME = NAME; return *this; }       \
			std::shared_ptr<void> NAME() { return _##NAME; }                                \
		private: std::shared_ptr<void> _##NAME

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
