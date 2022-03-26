#include "etc.hpp"

typedef std::map<std::string, int> variableContext; //Used to pass variables between nodes in a function
typedef std::map<std::string, std::string> variableTypeRegContext;  //Used to pass variable types

//BaseAST
//Code generation function that outputs to a file
void baseAST::codeGeneration(std::ofstream &outputFile) const {}
void baseAST::codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const {}
void baseAST::codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName) const {}
//Function used to update the variable contexts within a function (so variables in other code all refer to the same variable in other code in the same function)
void baseAST::updateContext() const {}
void baseAST::updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes) const {}
void baseAST::updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const {}
//Method to output a comment to the MIPS assembly file (comments are ignored by assembler)
std::string baseAST::outputComment(std::string outputComment) {
    std::string returnstring = "\n\t#" + outputComment + "\n";
    return returnstring;
}
//Other functions for other classes
void baseAST::addFunction(baseAST* newFunction) { }
void baseAST::addParameter(baseAST* newParam) {}
void baseAST::addStatement(baseAST* statement) {}