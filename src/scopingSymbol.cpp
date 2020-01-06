#include <symbols/scopingSymbol.hpp>

namespace symbols {

std::shared_ptr<variable> scopingSymbol::findVarByName(std::string name){
    std::list<std::shared_ptr<variable>>::iterator it;
    it = std::find(vars.begin(), vars.end(), name);
    return it != vars.end() ? *it : NULL;
}

std::shared_ptr<variable> scopingSymbol::createVariable(std::string name){
    if(findVarByName(name)){
        std::cerr << "Cannot redefine variable: " << name <<"\n";
        exit(1);
    }
    std::shared_ptr<variable> v(new variable(name, stackOffset));
    stackOffset -= 8;
    vars.push_back(v);
    return v;
}

void scopingSymbol::prologueCodeGen(std::ofstream& ofs){
    ofs << "push\t%rbp\nmov\t%rsp, %rbp\n";
}
void scopingSymbol::epilogueCodeGen(std::ofstream& ofs){
    ofs << "mov\t%rbp, %rsp\npop\t%rbp\nret\n";
}

}
