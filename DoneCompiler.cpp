#include <fstream>

#include "include/DoneCompiler.h"
#include "include/Preprocessor.h"
#include "include/DoneLexer.h"
#include "include/DoneParser.h"
#include "include/CodeGenerator.h"

void DoneCompiler::compile(std::string mainFile, std::string& projectPath) {
    Preprocessor preprocessor(mainFile, projectPath);
    preprocessor.runProcessor();
    std::string preProcessedCode = preprocessor.getGeneratedCode();

    ErrorHandler errorHandler;
    DoneLexer doneLexer(preProcessedCode, errorHandler);
    std::vector<Token> tokens = doneLexer.scanSourceCode();

    if (errorHandler.hasError) {
        errorHandler.report();
        exit(EXIT_FAILURE);
    }

    DoneParser doneParser(tokens, errorHandler);
    std::vector<Statement *> statements = doneParser.parseSourceCode();

    if (errorHandler.hasError) {
        errorHandler.report();
        exit(EXIT_FAILURE);
    }

    std::set<std::string> standardLibs = preprocessor.getStandardLibraries();

    CodeGenerator codeGenerator(errorHandler);
    codeGenerator.generateCode(statements, standardLibs);
    auto cSourceCode = codeGenerator.codeWriter.getSource();

    std::ofstream file(projectPath + outputCFileName);
    file << cSourceCode;
    file.close();
}

void DoneCompiler::setOutputCFileName(std::string fileName) {
    outputCFileName = std::move(fileName);
}

void DoneCompiler::setExecutableFileName(std::string fileName) {
    executableFileName = std::move(fileName);
}
