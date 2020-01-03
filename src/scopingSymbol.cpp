#include <symbols/scopingSymbol.hpp>

namespace symbols {

std::shared_ptr<variable> scopingSymbol::findVarByName(std::string name){
    std::list<std::shared_ptr<variable>>::iterator it;
    it = std::find(vars.begin(), vars.end(), name);
    return it != vars.end() ? *it : NULL;
}

// std::shared_ptr<variable> scopingSymbol::createVariable(std::string name, std::shared_ptr<expression> value){
//     if(findVarByName(name)){
//         std::cerr << "Cannot redefine variable: " << name <<"\n";
//         exit(1);
//     }
//     std::shared_ptr<variable> v(new variable(name, stackOffset, value);
//     stackOffset -= 8;
//     vars.push_back(v);
//     return v;
// }

}
