#ifndef etc_hpp
#define etc_hpp

#include <iostream>
#include <map>
#include <vector>

typedef std::map<std::string, int> variableContext; //Used to pass variables between nodes in a function
typedef std::map<std::string, std::string> variableTypeContext;  //Used to pass variable types

//Enum containing the different node types
enum nodeType {
    allFunctions_e,
    function_e
};

class baseAST {
    protected:
        nodeType node;
        variableContext nodeVariables;
        variableTypeContext nodeVariableTypes;
    public:
        //Pure virtual method that generates code into an output file in other nodes using the read-only context provided by a function node
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeContext nodeVariableTypes) = 0;
        //Pure virtual method that is used to update the variable context across a function and its code (must be called before codegen)
        virtual void updateContext(variableContext const nodeVariables, const variableTypeContext nodeVariableTypes) = 0;
};
#endif