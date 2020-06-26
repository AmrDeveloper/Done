#include <iostream>
#include <sstream>
#include <fstream>

#include "include/DoneLexer.h"

#define ENABLE_DEBUG_MODE

static void compile(const std::string& source, ErrorHandler& errorHandler) {
    DoneLexer doneLexer(source, errorHandler);

    std::vector<Token> tokens = doneLexer.scanSourceCode();

#ifdef  ENABLE_DEBUG_MODE
    std::vector<Token>::const_iterator token;
    for (token = tokens.begin(); token != tokens.end(); ++token) {
        std::cout << token->lexeme << std::endl;
    }
#endif

    if(errorHandler.hasError) {
        errorHandler.report();
        exit(EXIT_FAILURE);
    }
}

static void compileFile(const std::string& path, ErrorHandler& errorHandler) {
    std::ifstream file(path);
    std::ostringstream stream;
    stream << file.rdbuf();
    file.close();
    compile(stream.str(), errorHandler);
}

int main() {
    ErrorHandler errorHandler;
    compileFile("../source.done", errorHandler);
    return 0;
}
