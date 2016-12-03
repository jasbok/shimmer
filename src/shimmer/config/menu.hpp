#ifndef SHIMMER_COMMON_MENU_HPP
#define SHIMMER_COMMON_MENU_HPP

#include "common/event_system.hpp"
#include "common/regex_helpers.hpp"
#include "common/macros.hpp"
#include "config.hpp"
#include "menu_item.hpp"
#include <memory>
#include <unordered_map>

namespace shimmer
{
class menu
{
public:

        menu(const std::shared_ptr<event_system> event_system);
        virtual ~menu();

        void build_from ( const shimmer::config& conf );
private:
        typedef std::map<std::string, menu_item> item_map;
        typedef std::map<std::string, item_map> menu_map;
        menu_map _data;
        item_map::iterator _curr_item;
        item_map::iterator _curr_menu;
        std::shared_ptr<event_system> _event_system;
};
}

#endif
