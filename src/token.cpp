
#include <token.hpp>

namespace tokens {

std::vector<std::regex> token_regex_map(NUM_TOKEN_TYPES);

void init_token_regex_map(){
  token_regex_map[RETURN_KEYWORD] = "^return\\b";
  token_regex_map[INT_KEYWORD] = "^int\\b";
  token_regex_map[IF_KEYWORD] = "^if\\b";
  token_regex_map[ELSE_KEYWORD] = "^else\\b";
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
  token_regex_map[BOOL_AND] = "^\\&\\&";
  token_regex_map[EQUAL] = "^==";
  token_regex_map[NEQUAL] = "^!=";
  token_regex_map[LESS_THAN] = "^<";
  token_regex_map[GRATER_THAN] = "^>";
  token_regex_map[LESS_THAN_OR_EQUAL] = "^<=";
  token_regex_map[GREATE_THAN_OR_EQUAL] = "^>=";
  token_regex_map[ASSIGNMENT] = "^=";
  token_regex_map[QUESTION] = "^\\?";
  token_regex_map[COLON] = "^:";
}

void init_tokens(){
  init_token_regex_map();
}

}