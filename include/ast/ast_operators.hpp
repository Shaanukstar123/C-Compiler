#ifndef ast_statement.hpp
#define ast_statement.hpp

#include "ast.hpp"

class baseOP : public baseAST {
    baseAST* leftChild;
    baseAST* rightChild;
    baseOP(baseAST* leftChild, baseAST* rightChild) {
        leftChild = leftChild;
        rightChild = rightChild;
    }
};

class addOperator : public baseAST {
    
};


#endif