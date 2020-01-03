#ifndef __ENUMERATE_HPP
#define __ENUMERATE_HPP

#include <tuple>
#include <vector>

template <typename T>
class enumerate_impl
{
private:
    /* data */
    T& container;
public:
    struct item{
        size_t index;
        typename T::value_type& item;
    };
    typedef item value_type;

    struct iterator{
        iterator(typename T::iterator _it, size_t counter=0) :
            it(_it), counter(counter)
        {}
        
        iterator operator++(){
            return iterator(++it, ++counter);
        }

        bool operator!=(iterator other){
            return it != other.it;
        }

        typename T::iterator::value_type item(){
            return *it;
        }

        value_type operator*(){
            return value_type{counter, *it};
        }

        size_t index(){
            return counter;
        }
    private:
        typename T::iterator it;
        size_t counter;
    };
    enumerate_impl(T& t) : container(t){}
    
    iterator begin(){
        return iterator(container.begin());
    }

    iterator end(){
        return iterator(container.end());
    }
};

template <typename T>
enumerate_impl<T> enumerate(T& t){
    return enumerate_impl<T>(t);
}

// enumerate_impl::enumerate_impl(/* args */)
// {
// }

// enumerate_impl::~enumerate_impl()
// {
// }
#endif