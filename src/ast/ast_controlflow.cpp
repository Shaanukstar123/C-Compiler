#include "etc.hpp"

//While
While::While(int label, baseAST* expr) {
    //Create label for while
    whileLabel = "WHILE_" + std::to_string(label);
    endWhileLabel ="$ENDWHILE_" + std::to_string(label);
    expr = expr;
}
While::While(int label, baseAST* expr, baseAST* body) {
    //Create label for while
    whileLabel = "$WHILE_" + std::to_string(label);
    endWhileLabel ="$ENDWHILE_" + std::to_string(label);
    expr = expr;
    body = body;
}

void While::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {
    outputFile<<whileLabel<<":"<<std::endl;
    outputFile<<"lw "<<"$2,"<<expr<<std::endl;
    outputFile<<"nop"<<std::endl;
    outputFile<<"beq "<<"$2,"<<"$0,"<<endWhileLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    body->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    outputFile<<"b "<<whileLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
}
//If
If::If(int label, baseAST* ifExpr, baseAST* trueCond) {
    ifLabel = "$IF_" + std::to_string(label);
    exitLabel = "$EXITIF_" + std::to_string(label);
    ifExpr = ifExpr;
    trueCond = trueCond;
}
If::If(int label, baseAST* ifExpr, baseAST* trueCond, baseAST* falseCond) {
    ifLabel = "$IF_" + std::to_string(label);
    elseLabel = "$ELSE_" + std::to_string(label);
    exitLabel = "$EXITIF_" + std::to_string(label);
    ifExpr = ifExpr;
    trueCond = trueCond;
    falseCond = falseCond;
}
//Codegen
void If::codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string destReg) const {
    outputFile<<"lw "<<"$2,"<<ifExpr<<std::endl;
    outputFile<<"nop"<<std::endl;
    outputFile<<"beq "<<"$2,"<<"$0,"<<elseLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    trueCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    outputFile<<"b "<<exitLabel<<std::endl;
    outputFile<<"nop"<<std::endl;
    outputFile<<elseLabel<<":"<<std::endl;
    falseCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    outputFile<<"beq "<<"$0,$0,"<<exitLabel;
    outputFile<<exitLabel<<":"<<std::endl;
    
    //trueCond->codeGeneration(outputFile,nodeVariables,nodeVariableTypes,variableRegisters,destReg);
    //outputFile<<

}