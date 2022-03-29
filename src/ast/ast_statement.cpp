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
        statementList[i]->codeGeneration(outputFile, funcVariables, funcVariableTypes, funcVariablesReg, "$2");
    }
    
}
//Decleration with no expression
varDeclare::varDeclare(std::string varName) {
    var = varName;
}
varDeclare::varDeclare(std::string varName, baseAST* expression) {
    var = varName;
    expr = expression;
}
void varDeclare::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg) {
    //varDeclare should terminate context
    funcVariables.push_back({var, "0"});
    std::cout << "found variable: " << var << std::endl;
}

//A variable assignment
Assign::Assign(std::string varName, baseAST* varExpression) {
    var = varName;
    varExpr = varExpression;
}
//void Assign::updateContext(){
    //COMPLETE 
    
//}
void Assign::codeGeneration(std::ofstream &outputFile, variableContext const &funcVariables, variableTypeRegContext const &funcVariablesTypes, variableTypeRegContext const &funcVariablesReg, std::string destReg) const {
    std::cout << "assignment\n"; 
    bool foundVar = false;
    for(int i = 0; i < funcVariables.size(); i++) {
        std::cout << "var is present: " << funcVariables[i][0] << std::endl;
        if(funcVariables[i][0].compare(var) == 0) {
            foundVar = true;
        }
    }
    if(foundVar) {
        varExpr->codeGeneration(outputFile, funcVariables, funcVariablesTypes, funcVariablesReg, destReg);
    } else {
        std::cout << "Error variable " + var + " not declared" << std::endl;
    }
    //funcVariables[varName]=(funcVariables.size()*4)+4; //FIX UP
    outputFile<<"li $2,"<<varExpression<<std::endl;
    //outputFile<<"sw $2,"<<funcVariables[];
}

//A function call
//Function call
functionCall::functionCall(std::string funcT, std::string funcN) {
    funcName = funcN;
    funcType = funcT;
}
functionCall::functionCall(std::string funcT, std::string funcN, baseAST* paramLst) {
    funcName = funcN;
    funcType = funcT;
    paramList = paramLst;
}
