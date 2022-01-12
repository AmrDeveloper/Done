#include <fstream>
#include <sstream>
#include <filesystem>

#include "../include/DoneCompiler.h"
#include "../include/CompilerContext.h"
#include "../include/FileManager.h"
#include "../include/ErrorHandler.h"
#include "../include/DoneLexer.h"
#include "../include/DoneParser.h"
#include "../include/CodeGenerator.h"

DoneCompiler::DoneCompiler(CompilerOptions* compilerOptions) : compilerOptions(compilerOptions) {}

void DoneCompiler::compile() {
    auto* compilerContext = new CompilerContext();
    compilerContext->projectPath = compilerOptions->mainSourceFilePath;

    std::string sourceCode = readFileContent(compilerOptions->compilationPath);
    auto* doneLexer = new DoneLexer (sourceCode, compilerContext->errorHandler);
    DoneParser doneParser(compilerContext, doneLexer);
    std::vector<Statement *> statements = doneParser.parseSourceCode();

    CodeGenerator codeGenerator(compilerContext);
    auto cSourceCode = codeGenerator.generateCode(statements);
    
    for(auto statement : statements) delete statement;

    std::string cSourcefilePath = compilerOptions->mainSourceFilePath + "/" + compilerOptions->generatedFileName;
    writeFileContent(cSourcefilePath, cSourceCode);

    if (compilerOptions->generateExecutable) generateExecutable();
    if (compilerOptions->runExecutable) runExecutable();
}

void DoneCompiler::generateExecutable() {
    std::filesystem::current_path(compilerOptions->mainSourceFilePath);

    std::stringstream stream;
    stream << compilerOptions->compilerName;
    stream << " ";
    stream << compilerOptions->mainSourceFilePath << "/" << compilerOptions->generatedFileName;
    stream << " ";
    stream << "-o " << compilerOptions->executableFileName;
    stream << " ";
    stream << "-" << compilerOptions->optimizationLevel;

    std::string compileCommand = stream.str();
    std::system(compileCommand.data());
}

void DoneCompiler::runExecutable() {
    std::stringstream runExecutableCommand;
    runExecutableCommand << "./";
    runExecutableCommand << compilerOptions->executableFileName;

    std::string command = runExecutableCommand.str();
    std::system(command.data());
}