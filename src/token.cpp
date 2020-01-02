
#include <token.hpp>

namespace tokens {

std::map<token_type, std::regex> token_regex_map;
std::map<token_type, std::regex> keyword_regex_map;

void init_keyword_regex_map(){
  keyword_regex_map[RETURN_KEYWORD] = "^return\\b";
  keyword_regex_map[INT_KEYWORD] = "^int\\b";
}


void init_token_regex_map(){
  token_regex_map[IDENTIFIER] = "^[a-zA-Z_]\\w*";
  token_regex_map[INT_LITERAL] = "^[0-9]+";
  token_regex_map[PARENTH_OPEN] = "^\\(";
  token_regex_map[PARENTH_CLOSE] = "^\\)";
  token_regex_map[BRACE_OPEN] = "^\\{";
  token_regex_map[BRACE_CLOSE] = "^\\}";
  token_regex_map[MINUS] = "^-";
  token_regex_map[TILDE] = "^~";
  token_regex_map[EXCLAMATION_PT] = "^!";
  token_regex_map[SEMICOLON] = "^;";
  token_regex_map[PLUS] = "^\\+";
  token_regex_map[MULTIPLY] = "^\\*";
  token_regex_map[DIVIDE] = "^/";
  token_regex_map[BOOL_OR] = "^\\|\\|";
}

void init_tokens(){
  init_keyword_regex_map();
  init_token_regex_map();
}

}