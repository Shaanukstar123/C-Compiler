#include "etc.hpp"

typedef std::map<std::string, int> variableContext; //Used to pass variables between nodes in a function
typedef std::map<std::string, std::string> variableTypeRegContext;  //Used to pass variable types

//BaseAST
std::string baseAST::outputComment(std::string outputComment) {
    std::string returnstring = "\n\t#" + outputComment + "\n";
    return returnstring;
}