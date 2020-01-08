#ifndef __BLOCK_ITEM_HPP
#define __BLOCK_ITEM_HPP

#include "scopingSymbol.hpp"


namespace symbols {

// blockItems don't need any special functionality at this point
// Used solely as a classifier right now

class blockItem : virtual public symbol
{
private:
    /* data */
public:
    static std::shared_ptr<blockItem> parse(std::list<token>::iterator&, std::shared_ptr<scopingSymbol>);
    blockItem(/* args */);
    ~blockItem();
};

inline blockItem::blockItem(/* args */){}
inline blockItem::~blockItem(){}


}

#endif