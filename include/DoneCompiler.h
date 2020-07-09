
#ifndef DONELANG_DONECOMPILER_H
#define DONELANG_DONECOMPILER_H

#include <string>

#include "ErrorHandler.h"

#define C_SOURCE_FILE_NAME "main.c"
#define EXECUTABLE_SOURCE_FILE_NAME "main"

class DoneCompiler {
public:
    std::string outputCFileName = C_SOURCE_FILE_NAME;
    std::string executableFileName = EXECUTABLE_SOURCE_FILE_NAME;

    void compile(std::string mainFile, std::string &projectPath);
    void generateExecutable();
    void runExecutable();
    void setOutputCFileName(std::string fileName);
    void setExecutableFileName(std::string fileName);
};

#endif
