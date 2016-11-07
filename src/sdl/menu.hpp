#ifndef MENU_HPP
#define MENU_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace shimmer
{

template <typename L, typename V>
class menu_item
{
public:

        menu_item() {}

        menu_item ( const L& label, const V& value, const std::function<bool ( menu_item<L,V>& ) > &func )
                : _label ( label ), _value ( value ), _func ( func )
        {}

        virtual ~menu_item() {}

        L label() const
        {
                return _label;
        }
        void label ( const L &label )
        {
                _label = label;
        }

        V value() const
        {
                return _value;
        }
        void value ( const V &value )
        {
                _value = value;
        }

        std::function<void ( menu_item<L,V>& ) > function()
        {
                return _func;
        }

        void function ( const std::function<bool ( menu_item<L,V>& ) >& func )
        {
                _func = func;
        }

        bool operator() (){
                return _func(*this);
        }

private:
        L _label;
        V _value;
        std::function<bool ( menu_item<L,V>& ) > _func;
};

template<typename L, typename I>
class menu
{
public:
        menu() : _curr(0) {}
        menu ( const L& title, const std::vector<I>& items )
                : _title ( title ), _items ( items ), _curr(0)
        {}
        menu ( const L& title, std::vector<I>&& items )
                : _title ( title ), _items ( items ), _curr(0)
        {}

        virtual ~menu() {}

        L title() const
        {
                return _title;
        }
        void title ( const L &title )
        {
                _title = title;
        }

        I* parent() const
        {
                return _parent;
        }
        void parent ( I* parent )
        {
                _parent = parent;
        }

        std::vector<I> items() const
        {
                return _items;
        }
        void items ( const std::vector<I>& items )
        {
                _items = items;
        }
        void items ( std::vector<I>&& items )
        {
                _items = items;
        }

        void push_back ( const I& item )
        {
                _items.push_back ( item );
        }
        void push_back ( I&& item )
        {
                _items.push_back ( item );
        }

        I& next()
        {
                _curr += 1;
                _curr = _curr >= _items.size() ? 0 : _curr;
                return _items[_curr];
        }
        I& curr()
        {
                return _items[_curr];
        }
        I& prev()
        {
                _curr -= 1;
                _curr = _curr < 0 ? _items.size() - 1 : _curr;
                return _items[_curr];
        }

        size_t size(){
                return _items.size();
        }
private:
        L _title;
        I *_parent;
        std::vector<I> _items;
        size_t _curr;
};

template<typename K, typename M>
class menu_system
{
public:

        menu_system() {};
        virtual ~menu_system() {};

        void insert ( const K& key, const M& menu )
        {
                _menus[key] = menu;
        }
        void insert ( const K& key, M&& menu )
        {
                _menus[key] = menu;
        }

        M& get ( K key )
        {
                if ( _curr != key ) {
                        _history.push_back ( _curr );
                        _curr = key;
                }
                return _menus.at ( _curr );
        }

        M& curr()
        {
                return _menus.at ( _curr );
        }

        M& back()
        {
                if ( !_history.empty() ) {
                        _history.pop_back();
                        _curr = _history.back();
                }
                return _menus.at ( _curr );
        }
private:
        K _curr;
        std::unordered_map<K,M> _menus;
        std::vector<K> _history;
};
}

#endif
