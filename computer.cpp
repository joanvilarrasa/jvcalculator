#include "computer.h"
#include "tokenizer.h"
#include <cstddef>

int tokenIndex = 0;
int numberOfTokens = 0;
Token *tokenList = nullptr;

void printTree(Token *tree, int level) {
    if(tree == nullptr) {
        return;
    }
    printTree(tree->left, level + 1);
    for(int i = 0; i < level; i++) {
        Serial.print("  ");
    }
    if(tree->type == TOKEN_NUMBER) {
        Serial.println(String(tree->value));
    }
    else {
        Serial.println(tree->op);
    }
    printTree(tree->right, level + 1);
}

Token* parseExpression(int minPrecedence);

Token* getNextToken() {
    if(tokenIndex >= numberOfTokens) {
        return nullptr;
    }
    return &tokenList[tokenIndex];
    tokenIndex++;
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
    Serial.println();
    Serial.println("Result tree: ");
    printTree(resultTree, 0);
    Serial.println();
    return 0;
}