#include "etc.hpp"

addOperator::addOperator(baseAST* leftChild, baseAST* rightChild) {
    leftChild = leftChild;
    rightChild = rightChild;
}
void addOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg)const{
    leftChild->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters,"$8");//evaluate and store in temp regs
    rightChild->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters,"$9");
    outputFile<<"add $2,$8,$9"<<std::endl;
}