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

    std::set<std::string> standardLibs = preprocessor.getStandardLibraries();

    CodeGenerator codeGenerator(errorHandler);
    codeGenerator.generateCode(statements, standardLibs);
    auto cSourceCode = codeGenerator.codeWriter.getSource();

    for(auto statement : statements) {
        delete statement;
    }

    std::string cSourcefilePath = projectPath + outputCFileName;

    std::ofstream file(cSourcefilePath);
    file << cSourceCode;
    file.close();
}

void DoneCompiler::generateExecutable() {
    std::string gccCompileCommand;
    gccCompileCommand.append("gcc -o ");
    gccCompileCommand.append(executableFileName);
    gccCompileCommand.append(" ");
    gccCompileCommand.append(outputCFileName);

    system(gccCompileCommand.c_str());
}

void DoneCompiler::runExecutable() {
    std::string gccCompileCommand;
    //TODO : Issue while passing dot to system
    gccCompileCommand.append("./");
    gccCompileCommand.append(executableFileName);
    system(gccCompileCommand.c_str());
}

void DoneCompiler::setOutputCFileName(std::string fileName) {
    outputCFileName = std::move(fileName);
}

void DoneCompiler::setExecutableFileName(std::string fileName) {
    executableFileName = std::move(fileName);
}
