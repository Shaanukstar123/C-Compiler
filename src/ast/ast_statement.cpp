#include "etc.hpp"


codeBody::codeBody(baseAST* firstStatement) {
    this->addStatement(firstStatement);
}
void codeBody::addStatement(baseAST* statement) {
    statementList.push_back(statement);
}
void codeBody::updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg) {
    for(int i = 0; i < statementList.size(); i++) {
        statementList[i]->updateContext(funcVariables, funcVariableTypes, funcVariablesReg);
    }
}
//Decleration with no expression
varDeclare::varDeclare(std::string varName) {
    varName = varName;
}
varDeclare::varDeclare(std::string varName, baseAST* expression) {
    varName = varName;
    expression = expression;
}
void varDeclare::updateContext(variableContext const funcVariables, variableTypeRegContext const funcVariableTypes, variableTypeRegContext const funcVariablesReg) {
    expression->updateContext(funcVariables, funcVariableTypes, funcVariablesReg);
}

Assign::Assign(std::string varName, baseAST* varExpression) {
    varName = varName;
    varExpression = varExpression;
}
void Assign::codeGeneration(std::ofstream &outputFile, const variableContext funcVariables, const variableTypeRegContext funcVariablesTypes, const variableTypeRegContext funcVariablesReg, std::string regName) {
    if(variableRegisters.find("varName") == variableRegisters.end()) {
        varExpression->codeGeneration(outputFile, funcVariables, funcVariablesTypes, funcVariablesReg, regName);
    } else {
        std::cout << "Error variable " + varName + " not declared" << std::endl;
    }
}