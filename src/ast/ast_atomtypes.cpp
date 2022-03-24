#include "etc.hpp"

class NUMVAL : public baseAST {
    public:
        NUMVAL(int value) {
            int value = value;
        }

        void codeGen(std::ofstream &outputFile, int numvalue){
            outputFile<<"li "<<"$2,"<<numvalue;
        }
};