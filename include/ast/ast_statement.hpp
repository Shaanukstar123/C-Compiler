#ifndef ast_statement.hpp
#define ast_statement.hpp

#include "etc.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        void addStatement(baseAST* statement) {}
};
#endif