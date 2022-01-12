#ifndef DONELANG_COMPILEROPTION_H
#define DONELANG_COMPILEROPTION_H
#include <iostream>

#define COMPILER_NAME_FLAG          "-c"
#define OPTIMIZATION_FLAG           "-o"
#define GENERATED_FILE_NAME_FLAG    "-g"
#define EXECUTABLE_NAME_FLAG        "-e"
#define GENERATE_EXECUTABLE_FLAG    "-x"

#define COMPILER_HELP_FLAG          "-h"
#define COMPILER_VERSION_FLAG       "-v"

struct CompilerOptions {
    std::string mainSourceFileName;
    std::string mainSourceFilePath;
    std::string compilationPath;
    std::string compilerName            = "gcc";
    std::string optimizationLevel       = "O0";
    std::string generatedFileName       = "main.c";
    std::string executableFileName      = "main";
    bool generateExecutable             = false;
};

CompilerOptions* parseCompilerOptions(int argc, char** argv);

void parseCompilerFlags(char* flag);

#endif