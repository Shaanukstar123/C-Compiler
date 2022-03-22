#include "etc.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        void addStatement(baseAST* statement) {
            statementList.push_back(statement);
        }
};