#ifndef SHIMMER_CONFIG_MENU_ITEM_HPP
#define SHIMMER_CONFIG_MENU_ITEM_HPP

#include "common/macros.hpp"
#include <functional>
#include <string>
#include <vector>

namespace shimmer
{
class menu_item
{
public:

    enum class tags
    {
        CONFIG, LINK, SELECTED, UNAVAILABLE
    };

    menu_item() {}

    menu_item ( const std::string& label )
        : _label ( label )
    {}

    menu_item ( const std::string& label, const std::string& value )
        : _label ( label ),
          _value ( value )
    {}

    menu_item (
        const std::string& label,
        const std::string& value,
        const std::function<bool ( menu_item& ) >& func )
        : _label ( label ),
          _value ( value ),
          _func ( func )
    {}

    virtual ~menu_item() {}

    bool operator() ()
    {
        return _func ( *this );
    }

    menu_item& push_back ( enum tags tag )
    {
        _tags.push_back ( tag );
        return *this;
    }

    bool has ( enum tags tag ) const
    {
        for ( auto t : _tags ) {
            if ( tag == t ) return true;
        }

        return false;
    }

private:
    SHIMMER_MEMBER ( menu_item, std::string, label );

    SHIMMER_MEMBER ( menu_item, std::string, value );

    SHIMMER_MEMBER ( menu_item, std::vector<enum tags>, tags );

    SHIMMER_MEMBER ( menu_item, std::function<bool ( menu_item& ) >, func );
};
}

#endif
