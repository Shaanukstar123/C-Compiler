#ifndef etc_hpp
#define etc_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "ast/ast.hpp"
#include "ast/ast_atomtypes.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_keywords.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_controlflow.hpp"

extern const baseAST* generateAST(std::string c_source);
extern int labelCount;

#endif

/*
#ifndef ast_.hpp
#define ast_.hpp
#include "etc.hpp"

#endif
*/