#ifndef SHIMMER_CONFIG_MENU_BUILDER_HPP
#define SHIMMER_CONFIG_MENU_BUILDER_HPP

#include "common/event_system.hpp"
#include "config.hpp"
#include "menu.hpp"
#include <memory>
#include <string>

namespace shimmer
{
class menu_builder
{
public:
    typedef std::map<std::string, menu_item> shimmer_menu;

    typedef std::map<std::string, shimmer_menu> shimmer_menu_system;

    menu_builder ( const std::shared_ptr<event_system>& event_system );

    shimmer_menu_system build ( const config& conf );

    virtual ~menu_builder();

    static std::string format_title ( const std::string& str );

private:
    std::shared_ptr<event_system> _event_system;

    shimmer_menu_system _generate_menu_items ( const config& conf );
};
}

#endif
