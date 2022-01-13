#include <iostream>

#include "../include/CompilerOptions.h"
#include "../include/DoneCompiler.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Invalid number of arguments, use donec -h for help"
              << std::endl;
    return EXIT_FAILURE;
  }

  parseCompilerFlags(argv[1]);

  auto *compilerOptions = parseCompilerOptions(argc, argv);
  auto doneCompiler = DoneCompiler(compilerOptions);
  doneCompiler.compile();

  delete compilerOptions;
  return EXIT_SUCCESS;
}