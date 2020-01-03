#include <symbols/variable.hpp>

namespace symbols {

void variable::print(){
    std::cout << "VAR(" << name << "): ";
    if(!value){
        std::cout << "UNDF";
    } else {
        value->print();
    }
}

void variable::codeGen(std::ofstream& ofs){}


}