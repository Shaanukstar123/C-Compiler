#include "etc.hpp"

        
NUMVAL::NUMVAL(int value) {
    value = value;
}

void NUMVAL::updateContext() {

}

void NUMVAL::codeGeneration(std::ofstream &outputFile){
    outputFile<<"li "<<"$2,"<<value;
}