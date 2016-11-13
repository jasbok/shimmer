#include "attribute.hpp"

shimmer::attribute::attribute()
        : _size ( 1 )
{}

shimmer::attribute::attribute ( enum type type, GLint location, const std::string& name )
        : _type ( type ), _size ( 1 ), _location ( location ), _name ( name )
{}

shimmer::attribute::attribute ( enum type type, unsigned int size, GLint location, const std::string& name )
        : _type ( type ), _size ( size ), _location ( location ), _name ( name )
{}

shimmer::attribute::~attribute()
{}
