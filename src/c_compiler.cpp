#include "etc.hpp"

int main(int argc, char **argv) {
/*
  struct arguments arguments;
  Binding binding;

  // Default values for arguments
  arguments.source_file = 0;
  arguments.output_file = (char *)"a.out";
  arguments.level = warn;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  logger = new Log(arguments.level);
  logger->info("SOURCE_FILE = %s\n", arguments.source_file);
  logger->info("OUTPUT_FILE = %s\n", arguments.output_file);
*/  

    std::ofstream machine_code(argv[4]);
    const baseAST* ast = generateAST(argv[2]);
    ast->codeGeneration(machine_code);
    machine_code.close();

    //std::cerr << std::endl;
    //ast->print(std::cerr, 0);
    //std::cerr << std::endl;
    exit(0);
}
