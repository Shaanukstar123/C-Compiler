#include "etc.hpp"

typedef std::vector<std::vector<std::string>> variableContext; //Used to pass variables between nodes in a function
typedef std::vector<std::vector<std::string>> variableTypeRegContext;  //Used to pass variable types

//BaseAST

void baseAST::generateCode(std::ofstream &outputFile) const {};
void baseAST::codeGeneration(std::ofstream &outputFile) const {std::cout << "USING BASEAST codegen\n";}
void baseAST::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string regName) const {std::cout << "USING BASEAST codegen\n";}
//Function used to update the variable contexts within a function (so variables in other code all refer to the same variable in other code in the same function)
void baseAST::updateContext() {std::cout << "USING BASEAST updatecontext\n";}
void baseAST::updateContext(variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes) {std::cout << "USING BASEAST updatecontext\n";}
void baseAST::updateContext(variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes, variableTypeRegContext &variableRegisters) {std::cout << "USING BASEAST updatecontext\n";}
//Other functions
void baseAST::addFunction(baseAST* newFunction) {std::cout << "USING BASEAST addfunc\n";}
void baseAST::addParameter(baseAST* newParam) {std::cout << "USING BASEAST addparam\n";}
void baseAST::addStatement(baseAST* statement) {std::cout << "USING BASEAST addstate\n";}