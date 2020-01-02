
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <regex>

#include <token.hpp>
#include <symbols.hpp>

using namespace tokens;
using namespace symbols;

std::list<token> lex(std::istream_iterator<std::string> it){

  init_tokens();

  std::istream_iterator<std::string> eos;
  std::list<token> tokens;

  while(it != eos){
    std::string token_str = *it;
    std::cout << token_str << std::endl;
    token t;
    while(token_str.length() > 0){
      std::smatch match;
      int keyword = 0;
      int match_found = 0;
      for(std::pair<token_type, std::regex> tok_pair : keyword_regex_map){
        if(std::regex_search(token_str, match, tok_pair.second)){
          t.type = tok_pair.first;
          t.token_string = match.str();
          tokens.push_back(t);
          token_str = std::regex_replace(token_str, tok_pair.second, "", std::regex_constants::format_first_only);
          keyword = 1;
          break;
        }
      }
      if(keyword){
          continue;
      }
      for(std::pair<token_type, std::regex> tok_pair : token_regex_map){
        if(std::regex_search(token_str, match, tok_pair.second)){
          t.type = tok_pair.first;
          t.token_string = match.str();
          tokens.push_back(t);
          token_str = std::regex_replace(token_str, tok_pair.second, "", std::regex_constants::format_first_only);
          match_found = 1;
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
  for(token t : tokens){
    std::cout << t.type << ": " << t.token_string << "\n";
  }

  program *p = program::parse(tokens);

  p->codeGen(assembly_name);
  std::string gcc_command = "gcc " + assembly_name + " -o " + out_name;
  system(gcc_command.data());

  return 0;
}
