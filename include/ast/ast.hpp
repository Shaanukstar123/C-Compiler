#ifndef ast_hpp
#define ast_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class baseAST;

typedef std::vector<std::vector<std::string>> variableContext; //Used to pass variables between nodes in a function
typedef std::vector<std::vector<std::string>> variableTypeRegContext;  //Used to pass variable types

//Enum containing the different node types
enum nodeType {
    allFunctions_e,
    function_e,
    paramlist_e,
    param_e
};

class baseAST {
    protected:
        //Might not be needed but uses an enum to identify what type of node this is
        nodeType node;
        //A map of variable names and their values for functions to retain across all their code
        variableContext nodeVariables;
        //A map of variable names and their types
        variableTypeRegContext nodeVariableTypes;
        //A map of variable names and the registers they will be allocated to
        variableTypeRegContext variableRegisters;

        
    public:
        virtual void generateCode(std::ofstream &outputFile) const;
        //Code generation function that outputs to a file
        virtual void codeGeneration(std::ofstream &outputFile) const;
        virtual void codeGeneration(std::ofstream &outputFile, variableContext const &nodeVariables, variableTypeRegContext const &nodeVariableTypes, variableTypeRegContext const &variableRegisters, std::string regName) const;
        //Function used to update the variable contexts within a function (so variables in other code all refer to the same variable in other code in the same function)
        virtual void updateContext();
        virtual void updateContext(variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes);
        virtual void updateContext(variableContext &nodeVariables, variableTypeRegContext &nodeVariableTypes, variableTypeRegContext &variableRegisters);
        //Other functions
        virtual void addFunction(baseAST* newFunction);
        virtual void addParameter(baseAST* newParam);
        virtual void addStatement(baseAST* statement);
        virtual void addArg(baseAST* statement);
};

#endif