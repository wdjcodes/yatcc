
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

extern std::map<token_type, std::regex> token_regex_map;
extern std::map<token_type, std::regex> keyword_regex_map;

void init_tokens();

}

#endif
