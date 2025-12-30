#include "computer.h"
#include "tokenizer.h"
#include <cstddef>

struct TokenNode {
    Token token;
    TokenNode *left;
    TokenNode *right;
};

TokenNode* parseExpression(Token *tokens, int tokenCount, int &i, int minPrecedence);

TokenNode* getNextTokenNode(Token *tokens, int tokenCount, int &i) {
    if(i >= tokenCount) {
        return nullptr;
    }
    static TokenNode node;
    node.token = tokens[i++];
    node.left = nullptr;
    node.right = nullptr;
    return &node;
}

TokenNode* parseIncreasingPrecedence(Token *tokens, int tokenCount, int &i, TokenNode *left, int minPrecedence) {

    TokenNode *next = getNextTokenNode(tokens, tokenCount, i);
    if(next == nullptr) {
        return left;
    }
    if(next->token.type == TOKEN_NUMBER) {
        // This will never be reached
        i--;
        return left;
    }

    // Go up the tree because precedence is not increasing.
    if(next->token.value <= minPrecedence) {
        i--;
        return left;
    } 
    else {
        // Go down the tree because precedence is increasing. You go down the right side of the tree.
        TokenNode *rightNode = parseExpression(tokens, tokenCount, i, next->token.value);
        static TokenNode result;
        result.token = next->token;
        result.left = left;
        result.right = rightNode;
        return &result;
    }

}

TokenNode* parseExpression(Token *tokens, int tokenCount, int &i, int minPrecedence) {
    TokenNode *leftNode = getNextTokenNode(tokens, tokenCount, i);

    while (true) {
        TokenNode *nextLeftNode = parseIncreasingPrecedence(tokens, tokenCount, i, leftNode, minPrecedence);
        if(nextLeftNode == leftNode) { break; }
        leftNode = nextLeftNode;
    }

    return leftNode;
}

int calculateDfs(TokenNode *tree) {
    if(tree == nullptr) {
        return 0;
    }
    if(tree->token.type == TOKEN_NUMBER) {
        return tree->token.value;
    }

    int left = calculateDfs(tree->left);
    int right = calculateDfs(tree->right);
    if(tree->token.op == '+') {
        return left + right;
    }
    else if(tree->token.op == '-') { 
        return left - right;
    }
    else if(tree->token.op == '*') {
        return left * right;
    }
    else if(tree->token.op == '/') {
        return left / right;
    }
    return 0;
}

int computeResult(Token *tokens, int tokenCount) {
    int i = 0;
    TokenNode *resultTree = parseExpression(tokens, tokenCount, i, -1);
    int result = calculateDfs(resultTree);
    return result;
}


