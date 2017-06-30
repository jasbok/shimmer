#include "menu.hpp"

namespace shimmer
{
menu::menu ( const std::shared_ptr<event_system> event_system )
    : _event_system ( event_system )
{}

menu::~menu()
{}

void menu::build_from ( const config& conf )
{
    for ( auto entry : conf ) {
        std::cout << entry.first << std::endl;
        auto conf_split = split ( entry.first, "\\." );
        std::string curr_path = "root";

        for ( unsigned int i = 0; i < conf_split.size(); i++ ) {
            auto seg = conf_split[i];

            if ( i < ( conf_split.size() - 1 ) ) {
                _data[curr_path][conf_split[i]] = menu_item ( conf_split[i] )
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
                _data[curr_path][conf_split[i]] = menu_item (
                                                      conf_split[i],
                                                      entry.second );

                curr_path += "." + conf_split[i];
            }
        }
    }
}

}
