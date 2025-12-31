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

  // This should be its own struct but I want to keep things as simple as possible. This is for the computer. 
  int precedence;
  Token *left;
  Token *right;
};

int tokenizeQuery(char *query, Token *tokens);

#endif

