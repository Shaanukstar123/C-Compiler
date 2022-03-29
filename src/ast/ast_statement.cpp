#include "etc.hpp"

//Code body that contains a reference to all other ASTs
codeBody::codeBody(baseAST* firstStatement) {
    this->addStatement(firstStatement);
}
void codeBody::addStatement(baseAST* statement) {
    statementList.push_back(statement);
}
void codeBody::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg) {
    for(int i = 0; i < statementList.size(); i++) {
        statementList[i]->updateContext(funcVariables, funcVariableTypes, funcVariablesReg);
    }
    
}
//Code Generation

void codeBody::codeGeneration(std::ofstream &outputFile, variableContext const &funcVariables, variableTypeRegContext const &funcVariableTypes, variableTypeRegContext const &funcVariablesReg, std::string destReg) const{
    std::cout<<"Codebody\n";
    std::cout<<"number of statements: " << statementList.size()<<"\n";
    for (int i=0;i<statementList.size();i++){
        statementList[i]->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$2");
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
void varDeclare::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg) {
    //varDeclare should terminate context
    funcVariables.push_back({{varName, "0"}});
    std::cout << "found variable: " << varName << std::endl;
}

//A variable assignment
Assign::Assign(std::string varName, baseAST* varExpression) {
    varName = varName;
    varExpression = varExpression;
}
//void Assign::updateContext(){
    //COMPLETE 
    
//}
void Assign::codeGeneration(std::ofstream &outputFile, variableContext const &funcVariables, variableTypeRegContext const &funcVariablesTypes, variableTypeRegContext const &funcVariablesReg, std::string destReg) const {
    bool foundVar = false;
    for(int i = 0; i < funcVariables.size(); i++) {
        if(funcVariables[i][0].compare(varName) == 0) {
            foundVar = true;
        }
    }
    if(foundVar) {
        varExpression->codeGeneration(outputFile, funcVariables, funcVariablesTypes, funcVariablesReg, destReg);
    } else {
        std::cout << "Error variable " + varName + " not declared" << std::endl;
    }
    //funcVariables[varName]=(funcVariables.size()*4)+4; //FIX UP
    outputFile<<"li $2,"<<destReg<<std::endl;
    //outputFile<<"sw $2,"<<funcVariables[];
}

//A function call
//Function call
functionCall::functionCall(std::string funcType, std::string funcName) {
    funcName = funcName;
    funcType = funcType;
}
functionCall::functionCall(std::string funcType, std::string funcName, baseAST* paramList) {
    funcName = funcName;
    funcType = funcType;
    paramList = paramList;
}
