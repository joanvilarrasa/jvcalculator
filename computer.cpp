#include "computer.h"
#include "tokenizer.h"
#include <cstddef>

int tokenIndex = 0;
int numberOfTokens = 0;
Token *tokenList = nullptr;

void printToken(Token *token) {
    Serial.print("(");
    if(token->type == TOKEN_NUMBER) {
        Serial.print(String(token->value));
    }
    else {
        Serial.print(token->op);
    }
    Serial.print(")");
}

void printTree(Token *tree, int level) {
    if(tree == nullptr) {
        return;
    }
    // Left
    printTree(tree->left, level + 1);

    // Current
    for(int i = 0; i < level; i++) {
        Serial.print("  ");
    }
    printToken(tree);
    Serial.println();

    // Right
    printTree(tree->right, level + 1);
}

Token* parseExpression(int minPrecedence);

Token* getNextToken() {
    Serial.print("Getting next token: ");
    Serial.print(tokenIndex);
    Serial.print(" of ");
    Serial.print(numberOfTokens);
    if(tokenIndex >= numberOfTokens) {
        Serial.print("Reached end of token list");
        Serial.println();
        return nullptr;
    }
    Token *token = &tokenList[tokenIndex];
    printToken(token);
    Serial.println();
    tokenIndex++;
    return token;
}

Token* parseIncreasingPrecedence(Token *left, int minPrecedence) {

    Token *next = getNextToken();
    if(next == nullptr) {
        return left;
    }
    if(next->type == TOKEN_NUMBER) {
        // This will never be reached
        tokenIndex--;
        return left;
    }

    // Go up the tree because precedence is not increasing.
    if(next->precedence <= minPrecedence) {
        tokenIndex--;
        return left;
    } 
    else {
        // Go down the tree because precedence is increasing. You go down the right side of the tree.
        Token *rightNode = parseExpression(next->precedence);
        next->left = left;
        next->right = rightNode;
        return next;
    }

}

Token* parseExpression(int minPrecedence) {
    Token *leftNode = getNextToken();

    while (true) {
        Token *nextLeftNode = parseIncreasingPrecedence(leftNode, minPrecedence);
        if(nextLeftNode == leftNode) { break; }
        leftNode = nextLeftNode;
    }

    return leftNode;
}

// int calculateDfs(TokenNode *tree) {
//     if(tree == nullptr) {
//         return 0;
//     }
//     if(tree->token.type == TOKEN_NUMBER) {
//         return tree->token.value;
//     }

//     int left = calculateDfs(tree->left);
//     int right = calculateDfs(tree->right);
//     if(tree->token.op == '+') {
//         return left + right;
//     }
//     else if(tree->token.op == '-') { 
//         return left - right;
//     }
//     else if(tree->token.op == '*') {
//         return left * right;
//     }
//     else if(tree->token.op == '/') {
//         return left / right;
//     }
//     return 0;
// }

int computeResult(Token *tokens, int tokenCount) {
    tokenIndex = 0;
    numberOfTokens = tokenCount;
    tokenList = tokens;
    Token *resultTree = parseExpression(-1);
    Serial.println("Result tree: ");
    printTree(resultTree, 0);
    return 0;
}