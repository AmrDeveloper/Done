#include <fstream>

#include "../include/DoneCompiler.h"
#include "../include/CompilerContext.h"
#include "../include/FileManager.h"
#include "../include/ErrorHandler.h"
#include "../include/DoneLexer.h"
#include "../include/DoneParser.h"
#include "../include/CodeGenerator.h"

DoneCompiler::DoneCompiler(CompilerOptions* compilerOptions)
: compilerOptions(compilerOptions) {

}

void DoneCompiler::compile() {
    auto* compilerContext = new CompilerContext();
    compilerContext->projectPath = compilerOptions->mainSourceFilePath;

    std::string sourceCode = readFileContent(compilerOptions->compilationPath);
    auto* doneLexer = new DoneLexer (sourceCode, compilerContext->errorHandler);
    DoneParser doneParser(compilerContext, doneLexer);
    std::vector<Statement *> statements = doneParser.parseSourceCode();

    CodeGenerator codeGenerator(compilerContext);
    auto cSourceCode = codeGenerator.generateCode(statements);
    
    for(auto statement : statements) {
        delete statement;
    }

    std::string cSourcefilePath = compilerOptions->mainSourceFilePath + "/" + compilerOptions->generatedFileName;
    writeFileContent(cSourcefilePath, cSourceCode);
}