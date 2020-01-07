#ifndef __BLOCK_ITEM_HPP
#define __BLOCK_ITEM_HPP

#include "scopingSymbol.hpp"


namespace symbols {

// blockItems don't need any special functionality at this point
// Used solely as a classifier right now

class blockItem : public virtual symbol
{
private:
    /* data */
public:
    blockItem(/* args */);
    ~blockItem();
};

inline blockItem::blockItem(/* args */){}
inline blockItem::~blockItem(){}


}

#endif