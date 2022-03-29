#include "etc.hpp"

//While without codebody
While::While(int label, baseAST* expr) {
    //Creates labels for while
    whileLabel = "$WHILE_" + std::to_string(label);
    endWhileLabel ="$ENDWHILE_" + std::to_string(label);
    expression = expr;
    has_body = false; 
}
//While with codebody
While::While(int label, baseAST* expr, baseAST* body) {
    //Creates labels for while
    whileLabel = "$WHILE_" + std::to_string(label);
    endWhileLabel ="$ENDWHILE_" + std::to_string(label);
    expression = expr;
    bodyexpr = body;
    has_body = true;
}

void While::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {
    std::cout << "while" << std::endl;
    outputFile<<whileLabel<<":"<<std::endl;
    expression->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");
    outputFile<<"nop"<<std::endl;
    outputFile<<"beq "<<"$2,"<<"$0,"<<endWhileLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    if (has_body==true){
        bodyexpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);}
    outputFile<<"b "<<whileLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    outputFile<<endWhileLabel<<":"<<std::endl;
}
//If
If::If(int label, baseAST* ifExp, baseAST* trueCondition) {
    ifLabel = "$IF_" + std::to_string(label);
    exitLabel = "$EXITIF_" + std::to_string(label);
    ifExpr = ifExp;
    trueCond = trueCondition;
}
If::If(int label, baseAST* ifExp, baseAST* trueCondition, baseAST* falseCondition) {
    ifLabel = "$IF_" + std::to_string(label);
    elseLabel = "$ELSE_" + std::to_string(label);
    exitLabel = "$EXITIF_" + std::to_string(label);
    ifExpr = ifExp;
    trueCond = trueCondition;
    falseCond = falseCondition;
    hasElse = true;
}
//Codegen
void If::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {
    std::cout << "If" << std::endl;    
    //Evaluate expression
    ifExpr->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,"$2");
    if(hasElse == true) {
        outputFile<<"beq "<<"$2,"<<"$0,"<<elseLabel<<std::endl;
    } else {
        outputFile<<"beq "<<"$2,"<<"$0,"<<exitLabel<<std::endl;
    }
    outputFile<<"nop"<<std::endl;
    trueCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    outputFile<<"b "<<exitLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    if(hasElse == true) {
        outputFile<<elseLabel<<":"<<std::endl;
        falseCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
        outputFile<<"beq "<<"$0,$0,"<<exitLabel <<std::endl;
    }
    outputFile<<exitLabel<<":"<<std::endl;
    
    //trueCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    //outputFile<<

}

//For
For::For(int label, baseAST* var, baseAST* exit, baseAST* update, baseAST* code){
    label1 = "$1_" + std::to_string(label);
    label2 = "$2_" + std::to_string(label);
    label3 = "$3_" + std::to_string(label);
}

void For::updateContext(variableContext &funcVariables, variableTypeRegContext &funcVariableTypes, variableTypeRegContext &funcVariablesReg) {
    //For loop needs to store the variable it initalises into the stack
    //Maybe create new variable ast for it?
}

void For::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const{
    //For loop codegen
}