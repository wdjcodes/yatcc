
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <regex>

#include "token.hpp"

using namespace tokens;

std::list<token> lex(std::istream_iterator<std::string> it){

  init_tokens();

  std::istream_iterator<std::string> eos;
  std::list<token> tokens;

  while(it != eos){
    std::string token_str = *it;
    token t;
    while(token_str.length() > 0){
      std::smatch match;
      int keyword = 0;
      for(std::pair<token_type, std::regex> tok_pair : keyword_regex_map){
        if(std::regex_match(token_str, match, tok_pair.second)){
          t.type = tok_pair.first;
          t.token_string = match.str();
          tokens.push_back(t);
          keyword = 1;
          break;
        }
      }
      if(keyword){
          break;
      }
      for(std::pair<token_type, std::regex> tok_pair : token_regex_map){
        if(std::regex_search(token_str, match, tok_pair.second)){
          t.type = tok_pair.first;
          t.token_string = match.str();
          tokens.push_back(t);
          token_str = std::regex_replace(token_str, tok_pair.second, "", std::regex_constants::format_first_only);
          break;
        }
      }
    }
    it++;
  }
  return tokens;
}


int main(int argc, char const *argv[])
{
  
  std::list<token> tokens = lex(std::istream_iterator<std::string>(std::cin));
  for(token t : tokens){
    std::cout << t.type << ": " << t.token_string << "\n";
  }
  return 0;
}