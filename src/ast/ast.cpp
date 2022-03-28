#include "etc.hpp"

typedef std::vector<std::vector<std::string>> variableContext; //Used to pass variables between nodes in a function
typedef std::vector<std::vector<std::string>> variableTypeRegContext;  //Used to pass variable types

//BaseAST
std::string baseAST::outputComment(std::string outputComment) {
    std::string returnstring = "\n\t#" + outputComment + "\n";
    return returnstring;
}