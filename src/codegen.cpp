#include <map>
#include <codegen.hpp>

namespace codegen {

std::map<std::string, int> labelCountMap;

std::string genLabel(std::string label){
    std::map<std::string, int>::iterator it;

    it = labelCountMap.find(label);
    if(it == labelCountMap.end()){
        labelCountMap.insert(std::pair<std::string, int>(label, 0));
        it = labelCountMap.find(label);
    }

    return label + std::to_string((*it).second++);

}


}