#include "etc.hpp"

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