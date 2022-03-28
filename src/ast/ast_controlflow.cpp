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