#include <symbols/expressions/variable.hpp>

namespace symbols {

void variable::print(){
    std::cout << "VAR(" << name << "): ";
    if(!value){
        std::cout << "UNDF";
    } else {
        value->print();
    }
}

void variable::codeGen(std::ofstream& ofs){
    if(value){
        //This variable has been assigned to move the value off the stack
        ofs << "mov\t"<<  stackBaseOffset << "(%ebp), %rax\n";
    } else {
        //This variable has not been assigned to we will initialize to zero
        ofs << "mov\t$0,%rax\n";
    }
}


}