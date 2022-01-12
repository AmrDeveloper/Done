#ifndef DONELANG_COMPILERCONTEXT_H
#define DONELANG_COMPILERCONTEXT_H

#include <set>

#include "../include/ErrorHandler.h"

struct CompilerContext {
    std::string projectPath;
    std::set<std::string> cStdLibraries;
    std::set<std::string> scannedFiles;
    ErrorHandler errorHandler;
};

#endif