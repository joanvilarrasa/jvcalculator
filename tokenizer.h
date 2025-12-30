#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#define MAX_TOKENS 32

enum TokenType {
  TOKEN_NUMBER,
  TOKEN_OPERATOR
};
struct Token {
  TokenType type;
  int value;     
  char op; 
};

int tokenizeQuery(char *query, Token *tokens);

#endif

