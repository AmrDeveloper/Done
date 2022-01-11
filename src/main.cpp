#include <iostream>

#include "../include/DoneCompiler.h"
#include "../include/CompilerOptions.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Invalid number of arguments, use donec -h for help" << std::endl;
        return EXIT_FAILURE;
    }

    parseCompilerFlags(argv[1]);

    auto* compilerOptions = parseCompilerArguments(argc, argv);
    auto doneCompiler = DoneCompiler();
    doneCompiler.compile(compilerOptions);

    delete compilerOptions;
    return EXIT_SUCCESS;
}