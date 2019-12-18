
#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <regex>
#include <map>


namespace tokens {

enum token_type {
  // Keywords
  RETURN_KEYWORD,
  INT_KEYWORD,

  // Non-Keyword Tokens
  IDENTIFIER,
  INT_LITERAL,
  PARENTH_OPEN,
  PARENTH_CLOSE,
  BRACE_OPEN,
  BRACE_CLOSE,
  SEMICOLON
};

typedef struct token_t {
  token_type type;
  std::string token_string;
}token;

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
  token_regex_map[SEMICOLON] = "^;";
}

void init_tokens(){
  init_keyword_regex_map();
  init_token_regex_map();
}

}

#endif
