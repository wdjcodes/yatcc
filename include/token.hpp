
#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <regex>
#include <vector>


namespace tokens {

//TOKENS will be lexed as they appear in the following enum from top to bottom
//Changing the ordering of some tokens may cause lexxing to break
enum token_type {
  // Keywords
  RETURN_KEYWORD,     //RETURN_KEYWORD must come first - if it is moved the loop in 
  INT_KEYWORD,
  IF_KEYWORD,
  ELSE_KEYWORD,

  //Two character punctuation/operators
  BOOL_OR,
  BOOL_AND,
  EQUAL,
  NEQUAL,
  LESS_THAN_OR_EQUAL,
  GREATE_THAN_OR_EQUAL,

  //Single Character punctuation/operators
  PARENTH_OPEN,
  PARENTH_CLOSE,
  BRACE_OPEN,
  BRACE_CLOSE,
  MINUS,
  TILDE,
  EXCLAMATION_PT,
  SEMICOLON,
  PLUS,
  MULTIPLY,
  DIVIDE,
  LESS_THAN,
  GRATER_THAN,
  ASSIGNMENT,
  QUESTION,
  COLON,


  // Non-Keyword Tokens
  IDENTIFIER,
  INT_LITERAL,

  //Dummy Value - must be last in the enum
  NUM_TOKEN_TYPES
};

typedef struct token_t {
  token_type type;
  std::string token_string;
}token;

extern std::vector<std::regex>token_regex_map;

void init_tokens();

}

#endif
