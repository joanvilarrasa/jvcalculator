#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "tokenizer.h"

#include <Arduino.h>

struct Result {
    int value;     
    bool validResult;
};

void computeResult(Token *tokens, int tokenCount, Result *result);

#endif

