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
    std::string varLocation;
    for(int i = 0; i < funcVariables.size(); i++) {
        std::cout << "var is present: " << funcVariables[i][0] << std::endl;
        if(funcVariables[i][0].compare(var) == 0) {
            foundVar = true;
            varLocation = funcVariables[i][1];
        }
    }
    if(foundVar == true) {
        varExpr->codeGeneration(outputFile, funcVariables, funcVariablesTypes, funcVariablesReg, "$2");
    } else {
        std::cout << "Error variable " + var + " not declared" << std::endl;
    }
    outputFile << "sw $2, " << varLocation << "($fp)" << std::endl; 
}

//A function call
//Function call
functionCall::functionCall(std::string funcN) {
    funcName = funcN;
}
functionCall::functionCall(std::string funcN, baseAST* paramLst) {
    funcName = funcN;
    paramList = paramLst;
}

void functionCall::codeGeneration(std::ofstream &outputFile, variableContext const &funcVariables, variableTypeRegContext const &funcVariablesTypes, variableTypeRegContext const &funcVariablesReg, std::string destReg) const {
    outputFile << "jal " << funcName << std::endl;
    outputFile << "nop" << std::endl; 
}

//Function argument list
funcCallArgs::funcCallArgs(baseAST* firstArg) {
    this->addArg(firstArg);
}

void funcCallArgs::addArg(baseAST* newArg) {
    arguments.push_back(newArg);
}

void funcCallArgs::codeGeneration(std::ofstream &outputFile, variableContext const &funcVariables, variableTypeRegContext const &funcVariablesTypes, variableTypeRegContext const &funcVariablesReg, std::string destReg) const {
    //Code generation needs to loop through the arguments and sequentally place them in argument registes from 4-7
}