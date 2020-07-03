#include <sstream>
#include <fstream>

#include "include/DoneLexer.h"
#include "include/DoneParser.h"
#include "include/Preprocessor.h"
#include "include/CodeGenerator.h"

static void compile(const std::string& source, ErrorHandler& errorHandler) {
    DoneLexer doneLexer(source, errorHandler);

    std::vector<Token> tokens = doneLexer.scanSourceCode();

#ifdef ENABLE_DEBUG_MODE
    std::vector<Token>::const_iterator token;
    for (token = tokens.begin(); token != tokens.end(); ++token) {
        std::cout << token->lexeme << std::endl;
    }
#endif

    if(errorHandler.hasError) {
        errorHandler.report();
        exit(EXIT_FAILURE);
    }

    DoneParser doneParser(tokens, errorHandler);
    std::vector<Statement*> statements = doneParser.parseSourceCode();

    if(errorHandler.hasError) {
        errorHandler.report();
        exit(EXIT_FAILURE);
    }

    CodeGenerator codeGenerator(errorHandler);
    codeGenerator.generateCode(statements);
}

int main() {
    std::string projectPath = "../examples/";
    std::string mainFile = "Enume.done";

    Preprocessor preprocessor(mainFile, projectPath);
    preprocessor.runProcessor();
    std::string preProcessedCode = preprocessor.getGeneratedCode();

    ErrorHandler errorHandler;
    compile(preProcessedCode, errorHandler);

    return 0;
}
