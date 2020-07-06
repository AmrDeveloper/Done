#ifndef DONELANG_PREPROCESSOR_H
#define DONELANG_PREPROCESSOR_H

#include <set>
#include <stack>
#include <string>

#define IMPORT "import"
#define INCLUDE "include"

#define TRUE_VAL 1
#define FALSE_VAL 0

#define LOAD "@LOAD "
#define END "@END"
#define IGNORE "@IGNORE"

class Preprocessor {

public:
    Preprocessor(std::string& mainFile, std::string& projectPath);
    void runProcessor();
    std::string getGeneratedCode();
    std::set<std::string> getStandardLibraries();

private:
    std::string sourcePath;
    std::string currentFile;
    std::string generatedCode;
    std::set<std::string> standardLibraries;
    std::set<std::string> sourceVisitedFiles;
    std::stack<std::string> sourceDepthStack;

    bool insertUniqueFile(const std::string& filePath);
    void parserFileDependency(const std::string& filePath);

    void scanImportKeyword(std::string& library);
    void scanIncludeKeyword(std::string& line);

    void generateLoadLabel(const std::string& string);
    void generateEndLabel();
    void generateIgnoreLabel();

    std::string popNewSourceFile();
};

#endif
