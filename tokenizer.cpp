#include "tokenizer.h"

int tokenizeQuery(char *query, Token *tokens) {
  int tokenCount = 0;
  int i = 0;
  
  while(i < 64 && tokenCount < MAX_TOKENS) {
    // Skip whitespace
    while(i < 64 && (query[i] == ' ' || query[i] == '\0')) {
      i++;
    }
    
    if(i >= 64) {
      break;
    }
    
    char c = query[i];
    
    if(c >= '0' && c <= '9') {
      int num = 0;
      while(i < 64 && query[i] >= '0' && query[i] <= '9') {
        num = num * 10 + (query[i] - '0');
        i++;
      }
      tokens[tokenCount].type = TOKEN_NUMBER;
      tokens[tokenCount].value = num;
      tokens[tokenCount].op = '\0';
      tokenCount++;
    }
    else if(c == '+' || c == '-' || c == '*' || c == '/') {
      tokens[tokenCount].type = TOKEN_OPERATOR;
      tokens[tokenCount].value = 0;
      tokens[tokenCount].op = c;
      tokenCount++;
      i++;
    }
    else {
      i++;
    }
  }
  
  return tokenCount;
}

