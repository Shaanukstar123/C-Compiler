#include "etc.hpp"

//While
While::While(int label, baseAST* expr) {
    //Create label for while
    whileLabel = "WHILE_" + std::to_string(label);
    expr = expr;
}
While::While(int label, baseAST* expr, baseAST* body) {
    //Create label for while
    whileLabel = "WHILE_" + std::to_string(label);
    expr = expr;
    body = body;
}

//If
If::If(int label, baseAST* ifExpr, baseAST* trueCond) {
    ifLabel = "IF_" + std::to_string(label);
    exitLabel = "EXITIF_" + std::to_string(label);
    ifExpr = ifExpr;
    trueCond = trueCond;
}
If::If(int label, baseAST* ifExpr, baseAST* trueCond, baseAST* falseCond) {
    ifLabel = "IF_" + std::to_string(label);
    elseLabel = "ELSE_" + std::to_string(label);
    exitLabel = "EXITIF_" + std::to_string(label);
    ifExpr = ifExpr;
    trueCond = trueCond;
    falseCond = falseCond;
}
