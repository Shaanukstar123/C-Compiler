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

//Less than
lessThan::lessThan(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void lessThan::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "less than operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
}

//Greater than
greaterThan::greaterThan(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void greaterThan::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "greater than operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
}

//lessThanEqual
lessThanEqual::lessThanEqual(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void lessThanEqual::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "less than equals operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
}

//GreaterThanEqual
greaterThanEqual::greaterThanEqual(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void greaterThanEqual::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "greather than equals operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
}

//Incrementation
increment::increment(std::string var) {
    varRef = var;
}
void increment::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "greater than equals operation\n";
    //Retrieve variable and store in register 8?
    //Now need to add one and store the variable again - maybe make an addition baseAST, pass in context and do codegen?
}
