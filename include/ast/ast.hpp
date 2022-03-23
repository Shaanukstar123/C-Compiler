#ifndef ast_hpp
#define ast_hpp

#include "etc.hpp"

typedef std::map<std::string, int> variableContext; //Used to pass variables between nodes in a function
typedef std::map<std::string, std::string> variableTypeRegContext;  //Used to pass variable types

//Enum containing the different node types
enum nodeType {
    allFunctions_e,
    function_e,
    paramlist_e,
    param_e
};

class baseAST {
    protected:
        nodeType node;
        variableContext nodeVariables;
        variableTypeRegContext nodeVariableTypes;
        variableTypeRegContext variableRegisters;
    public:
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const = 0;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes) const = 0;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const = 0;
        std::string outputComment(std::string outputComment) {}
};

#endif