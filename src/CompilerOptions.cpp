#include <cstring>

#include "../include/CompilerOptions.h"
#include "../include/FileManager.h"

CompilerOptions* parseCompilerArguments(int argc, char** argv) {
    CompilerOptions* compilerOptions = new CompilerOptions;
    compilerOptions->mainSourceFileName = getFileName(argv[1]);
    compilerOptions->mainSourceFilePath = getFileParentPath(argv[1]);
    compilerOptions->compilationPath = argv[1];

    for(int i = 2; i < argc ; i++) {
        if (strcmp(argv[i], COMPILER_NAME_FLAG) == 0 && i < argc - 1) {
            compilerOptions->compilerName = argv[i + 1];
            i = i + 2;
        }

        if (strcmp(argv[i], OPTIMIZATION_FLAG) == 0 && i < argc - 1) {
            compilerOptions->optimizationLevel = argv[i + 1];
            i = i + 2;
        }

        if (strcmp(argv[i], GENERATED_FILE_NAME_FLAG) == 0 && i < argc - 1) {
            compilerOptions->generatedFileName = argv[i + 1];
            i = i + 2;
        }
        if (strcmp(argv[i], EXECUTABLE_NAME_FLAG) == 0 && i < argc - 1) {
            compilerOptions->executableFileName = argv[i + 1];
            i = i + 2;
        }
    }

    return compilerOptions;
}
 
void parseCompilerFlags(char* flag) {
    if (strcmp(flag, COMPILER_HELP_FLAG) == 0) {
        std::cout << "Done is compiler to generate C" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "    donec <source file> <options>" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (strcmp(flag, COMPILER_VERSION_FLAG) == 0) {
        std::cout << "Done Compiler version is 1.0.0" << std::endl;
        exit(EXIT_SUCCESS);
    }
}