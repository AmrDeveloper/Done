
#include "include/Preprocessor.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Preprocessor::Preprocessor(std::string &mainFile, std::string & projectPath) {
    sourcePath = projectPath;
    sourceDepthStack.push(sourcePath + mainFile);
}

void Preprocessor::runProcessor() {
    while(!sourceDepthStack.empty()) {
        currentFile = popNewSourceFile();

        bool isUnique = insertUniqueFile(currentFile);
        if(isUnique == FALSE_VAL) continue;
        parserFileDependency(currentFile);
    }
}

bool Preprocessor::insertUniqueFile(const std::string &filePath) {
    return sourceVisitedFiles.insert(filePath).second;
}

void Preprocessor::parserFileDependency(const std::string &filePath) {
    generateLoadLabel(filePath);
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind(IMPORT, 0) == 0) {
                scanImportKeyword(line);
            } else if (line.rfind(INCLUDE, 0) == 0) {
                scanIncludeKeyword(line);
            } else {
                generatedCode.append(line + "\n");
            }
        }
        file.close();
    }else{
        //TODO : file is not exists should add error by error handler
    }
    generateEndLabel();
}

void Preprocessor::scanImportKeyword(std::string &library) {
    library.replace(0, 6 , "");
    library.erase(remove(library.begin(), library.end(), '\"' ),library.end());
    library.erase(remove(library.begin(), library.end(), ' ' ),library.end());

    std::string libraryPath = sourcePath + library;

    bool isVisited = insertUniqueFile(libraryPath);
    // Make sure one file can't import other file twice
    if(isVisited == FALSE_VAL) return;

    sourceDepthStack.push(libraryPath);
    currentFile = libraryPath;

    parserFileDependency(currentFile);
    currentFile = popNewSourceFile();
}

void Preprocessor::scanIncludeKeyword(std::string &library) {
    library.replace(0, 7 , "");
    library.erase(remove(library.begin(), library.end(), '\"' ),library.end());
    library.erase(remove(library.begin(), library.end(), ' ' ),library.end());
    standardLibraries.insert(library);
    generateIgnoreLabel();
}

void Preprocessor::generateLoadLabel(const std::string &filePath) {
    generatedCode.append(LOAD + filePath);
    generatedCode.append("\n");
}

void Preprocessor::generateEndLabel() {
    generatedCode.append(END);
    generatedCode.append("\n");
}

void Preprocessor::generateIgnoreLabel() {
    generatedCode.append(IGNORE);
    generatedCode.append("\n");
}

std::string Preprocessor::popNewSourceFile() {
    std::string source = sourceDepthStack.top();
    sourceDepthStack.pop();
    return source;
}

std::string Preprocessor::getGeneratedCode() {
    return generatedCode;
}

std::set<std::string> Preprocessor::getStandardLibraries() {
    return standardLibraries;
}
