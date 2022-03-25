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
        //Might not be needed but uses an enum to identify what type of node this is
        nodeType node;
        //A map of variable names and their values for functions to retain across all their code
        variableContext nodeVariables;
        //A map of variable names and their types
        variableTypeRegContext nodeVariableTypes;
        //A map of variable names and the registers they will be allocated to
        variableTypeRegContext variableRegisters;
    public:
        //Code generation function that outputs to a file
        virtual void codeGeneration(std::ofstream &outputFile) const = 0;
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const = 0;
        virtual void codeGeneration(std::ofstream &outputFile, const variableContext nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters, std::string regName) const = 0;
        //Function used to update the variable contexts within a function (so variables in other code all refer to the same variable in other code in the same function)
        virtual void updateContext() const = 0;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes) const = 0;
        virtual void updateContext(variableContext const nodeVariables, const variableTypeRegContext nodeVariableTypes, const variableTypeRegContext variableRegisters) const = 0;
        //Method to output a comment to the MIPS assembly file (comments are ignored by assembler)
        std::string outputComment(std::string outputComment) {
            std::string returnstring = "\n\t#" + outputComment + "\n";
            return returnstring;
        }
};