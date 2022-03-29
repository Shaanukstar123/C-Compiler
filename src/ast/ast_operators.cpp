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

//Multiply
multOperator::multOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void multOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "multi operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //Multiply
    outputFile<<"mult $8,$9"<<std::endl;
    outputFile <<"mflo $2" << std::endl;
}

//Divide
divOperator::divOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void divOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "div operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //Multiply
    outputFile<<"div $8,$9"<<std::endl;
    outputFile <<"mflo $2" << std::endl;
}


//Comparisons
equivalenceOperator::equivalenceOperator(baseAST* leftChild, baseAST* rightChild, int label) {
    branchLabel = "$Branch_" + std::to_string(label);
    leftOp = leftChild;
    rightOp = rightChild;
}
void equivalenceOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "equivalance operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
    outputFile << "seq " << destReg << ",$8,$9" << std::endl;
}

//Less than
lessThan::lessThan(baseAST* leftChild, baseAST* rightChild, int label) {
    branchLabel = "$Branch_" + std::to_string(label);
    leftOp = leftChild;
    rightOp = rightChild;
}
void lessThan::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "less than operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
    outputFile << "slt " << destReg << ",$8,$9" << std::endl;
    
}

//Greater than
greaterThan::greaterThan(baseAST* leftChild, baseAST* rightChild, int label) {
    branchLabel = "$Branch_" + std::to_string(label);
    leftOp = leftChild;
    rightOp = rightChild;
}
void greaterThan::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "greater than operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
    outputFile << "sgt " << destReg << ",$8,$9" << std::endl;
}

//lessThanEqual
lessThanEqual::lessThanEqual(baseAST* leftChild, baseAST* rightChild, int label) {
    branchLabel = "$Branch_" + std::to_string(label);
    leftOp = leftChild;
    rightOp = rightChild;
}
void lessThanEqual::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "less than equals operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
    outputFile << "sle " << destReg << ",$8,$9" << std::endl;
}

//GreaterThanEqual
greaterThanEqual::greaterThanEqual(baseAST* leftChild, baseAST* rightChild, int label) {
    branchLabel = "$Branch_" + std::to_string(label);
    leftOp = leftChild;
    rightOp = rightChild;
}
void greaterThanEqual::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::string branchEnd = branchLabel+"end";
    std::cout << "greather than equals operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    //outputFile<<"sub $2,$8,$9"<<std::endl;
    outputFile << "sge " << destReg << ",$8,$9" << std::endl;
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

//LOGICAL OPERATORS

//Logical AND

logicalAndOperator::logicalAndOperator(baseAST* leftChild, baseAST* rightChild, int label) {
    leftOp = leftChild;
    rightOp = rightChild;
    branchLabel = "$Branch_" + std::to_string(label);
    
}
void logicalAndOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::string endLabel = "End" + branchLabel;
    std::cout << "logical AND operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    
    outputFile<<"beq $8,$0,"<<branchLabel<<std::endl;
    outputFile<<"nop"<<std::endl;

    outputFile<<"beq $9,$0,"<<branchLabel<<std::endl;
    outputFile<<"nop"<<std::endl;

    outputFile<<"li $2,1"<<std::endl;
    outputFile<<"b "<<endLabel<<std::endl;
    outputFile<<"nop"<<std::endl;

    outputFile<<branchLabel<<":"<<std::endl;
    outputFile<<"mov $2,$0"<<std::endl;

    outputFile<<"b "<<endLabel<<std::endl;
    outputFile<<"nop"<<std::endl;

    outputFile<<endLabel<<":"<<std::endl;
    
}

logicalOrOperator::logicalOrOperator(baseAST* leftChild, baseAST* rightChild, int label) {
    leftOp = leftChild;
    rightOp = rightChild;
    branchLabel = "$Branch_" + std::to_string(label);
}
void logicalOrOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::string endLabel = "End" + branchLabel;
    std::cout << "logical AND operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"OR $2,$8,$9"<<std::endl;
}

//BITWISE OPERATORS

bitwiseAndOperator::bitwiseAndOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void bitwiseAndOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "logical AND operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"AND $2,$8,$9"<<std::endl;
}

bitwiseOrOperator::bitwiseOrOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void bitwiseOrOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "logical AND operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"OR $2,$8,$9"<<std::endl;
}

bitwiseXorOperator::bitwiseXorOperator(baseAST* leftChild, baseAST* rightChild) {
    leftOp = leftChild;
    rightOp = rightChild;
}
void bitwiseXorOperator::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    std::cout << "logical AND operation\n";
    leftOp->codeGeneration(outputFile, nodeVariables, nodeVariableTypes, variableRegisters, "$8");//evaluate and store in temp regs
    rightOp->codeGeneration(outputFile, nodeVariables,nodeVariableTypes, variableRegisters, "$9");
    outputFile<<"XOR $2,$8,$9"<<std::endl;
}
