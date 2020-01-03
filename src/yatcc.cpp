
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <regex>

#include <token.hpp>
#include <symbols.hpp>
#include <enumerate.hpp>

using namespace tokens;
using namespace symbols;

std::list<token> lex(std::istream_iterator<std::string> it){

  init_tokens();

  std::istream_iterator<std::string> eos;
  std::list<token> tokens;

  while(it != eos){
    std::string token_str = *it;
    token t;
    while(token_str.length() > 0){
      std::smatch match;
      int match_found = 0;
      for(auto re_it : enumerate(token_regex_map)){
        std::regex r = re_it.item;
        if(std::regex_search(token_str, match, r)){
          t.type = (token_type)re_it.index;
          t.token_string = match.str();
          tokens.push_back(t);
          token_str = std::regex_replace(token_str, r, "", std::regex_constants::format_first_only);
          match_found = 1;
          std::cout << t.type << ": " << t.token_string << "\n";
          break;
        }
      }
      if(!match_found){
        std::cerr << "Bad Token: " << token_str << std::endl;
        exit(1);
      }
    }
    it++;
  }
  return tokens;
}


int main(int argc, char const *argv[])
{
  std::istream_iterator<std::string> is_it;
  std::string out_name, assembly_name;
  std::ifstream ifs;
  if(argc == 2){
    ifs.open(argv[1]);
    std::string line;
    is_it = std::istream_iterator<std::string>(ifs);    
    std::smatch m;
    out_name = argv[1];
    out_name = out_name.substr(0, out_name.find_last_of("."));
    assembly_name = out_name + ".S";
  } else {
    is_it = std::cin;
    out_name = "test";
    assembly_name = "test.S";
  }

  std::list<token> tokens = lex(is_it);
  program *p = program::parse(tokens);

  p->codeGen(assembly_name);
  std::string gcc_command = "gcc " + assembly_name + " -o " + out_name;
  system(gcc_command.data());

  return 0;
}
