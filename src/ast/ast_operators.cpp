#include "etc.hpp"

//Addition
addOperator::addOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void addOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "add operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"add $2,$8,$9"<<std::endl;
}

//Subtraction
subOperator::subOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void subOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "sub operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"sub $2,$8,$9"<<std::endl;
}

//Comparisons
equivalenceOperator::equivalenceOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void equivalenceOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "equivalance operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
}
