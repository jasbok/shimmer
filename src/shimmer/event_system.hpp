#ifndef EVENT_HPP
#define EVENT_HPP

#include "./common/event.hpp"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace shimmer
{
template<typename C = context_type, typename I = event_type, typename E = event<>>
class event_system
{
public:
        typedef std::function<void ( const E& event ) > event_function;
        typedef std::unordered_map<I, std::vector<event_function>> event_map;

        void context ( const C& context )
        {
                _context = context;
        }

        void emit ( const I& name, const E& event )
        {
                for ( auto func : _context_map[_context][name] ) {
                        func ( event );
                }
        }
        void bind ( const I& name, std::function<void ( const E& event ) > func )
        {
                _context_map[_context][name].push_back ( func );
        }
private:
        C _context;
        std::unordered_map<C, event_map> _context_map;
};
}

#endif

