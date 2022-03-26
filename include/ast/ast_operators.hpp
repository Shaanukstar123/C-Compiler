#ifndef ast_operators.hpp
#define ast_operators.hpp

#include "ast.hpp"

class baseOP : public baseAST {
    public:
        baseAST* leftChild;
        baseAST* rightChild;
};

class addOperator : public baseAST {
    public:
        addOperator(baseAST* leftChild, baseAST* rightChild);
};

#endif