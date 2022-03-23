#include "etc.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        void addStatement(baseAST* statement) {
            statementList.push_back(statement);
        }
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes) {
            for(int i = 0; i < statementList.size(); i++) {
                statementList[i]->updateContext(funcVariables, funcVariableTypes);
            }
        }
};