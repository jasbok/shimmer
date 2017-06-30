#include "menu_builder.hpp"
#include "common/regex_helpers.hpp"
#include <algorithm>
#include <iostream>

namespace shimmer
{
menu_builder::menu_builder ( const std::shared_ptr<event_system>& event_system )
    : _event_system ( event_system )
{}

menu_builder::~menu_builder()
{}

menu_builder::shimmer_menu_system menu_builder::build ( const config& conf )
{
    shimmer_menu_system ret;

    for ( auto menu_entry : _generate_menu_items ( conf ) ) {
        std::cout << "menu entry: " << menu_entry.first << std::endl;

        for ( auto item_entry : menu_entry.second ) {
            std::cout << "menu item [" << item_entry.first << "]: "
                      << item_entry.second.label()
                      << ( item_entry.second.has ( menu_item::tags::LINK )
                           ? "->"
                           : "=" )
                      << item_entry.second.value() << std::endl;
        }
    }

    return ret;
}

std::string menu_builder::format_title ( const std::string& str )
{
    auto ret = transform ( str, "\\b.", [] ( const std::string& match ) {
        std::string m = match;
        std::transform ( m.begin(), m.end(), m.begin(), ::toupper );

        return m;
    } );

    return std::regex_replace ( ret, std::regex ( "_" ), " " );
}

menu_builder::shimmer_menu_system menu_builder::_generate_menu_items ( const config& conf )
{
    shimmer_menu_system items;

    for ( auto entry : conf ) {
        std::cout << entry.first << std::endl;
        auto conf_split = split ( entry.first, "\\." );
        std::string curr_path = "root";

        for ( unsigned int i = 0; i < conf_split.size(); i++ ) {
            auto seg = conf_split[i];

            if ( i < ( conf_split.size() - 1 ) ) {
                items[curr_path][conf_split[i]] = menu_item ( conf_split[i] )
                                                  .value ( curr_path
                                                          + "."
                                                          + conf_split[i] )
                                                  .push_back ( menu_item::tags::LINK )
                .func ( [this] ( menu_item& item ) {
                    _event_system->menu_change.emit ( item.value() );
                    return true;
                } );

                curr_path += "." + conf_split[i];
            } else {
                items[curr_path][conf_split[i]] = menu_item (
                                                      conf_split[i],
                                                      entry.second );

                curr_path += "." + conf_split[i];
            }
        }
    }

    return items;
}
}
