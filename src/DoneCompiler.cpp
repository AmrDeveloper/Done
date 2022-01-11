#include <fstream>

#include "../include/DoneCompiler.h"
#include "../include/FileManager.h"
#include "../include/ErrorHandler.h"
#include "../include/Preprocessor.h"
#include "../include/DoneLexer.h"
#include "../include/DoneParser.h"
#include "../include/CodeGenerator.h"


DoneCompiler::DoneCompiler(CompilerOptions* compilerOptions)
: compilerOptions(compilerOptions) {

}

void DoneCompiler::compile() {
    Preprocessor preprocessor(compilerOptions->mainSourceFileName, compilerOptions->mainSourceFilePath);
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

    std::string cSourcefilePath = compilerOptions->mainSourceFilePath + "/" + compilerOptions->generatedFileName;
    writeFileContent(cSourcefilePath, cSourceCode);
}