#ifndef ast_controlflow.hpp
#define ast_controlflow.hpp
#include "ast.hpp"

class While : public baseAST {
    public:
        std::string whileLabel;
        baseAST* expr;
        baseAST* body;
        While(int label, baseAST* expr);
        While(int label, baseAST* expr, baseAST* code);
};


#endif
