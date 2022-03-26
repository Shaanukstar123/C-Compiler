#include "etc.hpp"

class codeBody : public baseAST{
    public:
        std::vector<baseAST*> statementList;
        void addStatement(baseAST* statement) {
            statementList.push_back(statement);
        }
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg) {
            for(int i = 0; i < statementList.size(); i++) {
                statementList[i]->updateContext(funcVariables, funcVariableTypes, funcVariablesReg);
            }
        }
                
            
        
};

class decleration : public baseAST{
    public:
        std::string varName;
        baseAST* expression;
        //Decleration with no expression
        decleration(std::string varName) {
            varName = varName;
        }
        decleration(std::string varName, baseAST* expression) {
            varName = varName;
            expression = expression;
        }
        void updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg) {
            expression->updateContext(funcVariables, funcVariableTypes, funcVariablesReg);
        }
};

class Assign : public baseAST {
    public:
        std::string varName;
        baseAST* varExpression;
        Assign(std::string varName, baseAST* varExpression) {
            varName = varName;
            varExpression = varExpression;
        }
        void codeGeneration(std::ofstream &outputFile, const variableContext funcVariables, const variableTypeRegContext funcVariablesTypes, const variableTypeRegContext funcVariablesReg, std::string regName) {
            if(variableRegisters.find("varName") == variableRegisters.end()) {
                varExpression->codeGeneration(outputFile, funcVariables, funcVariablesTypes, funcVariablesReg, regName);
            } else {
                std::cout << "Error variable " + varName + " not declared" << std::endl;
            }
        }
};