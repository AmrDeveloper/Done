#include "../include/ErrorHandler.h"
#include <iostream>

Error::Error(std::string aFile, int aLine, int aStart, int aEnd,
        std::string aMessage, std::string aPosition) {
    fileName = std::move(aFile);
    line = aLine;
    start = aStart;
    end = aEnd;
    message = std::move(aMessage);
    position = std::move(aPosition);
}

Error::Error(int aLine, int aStart, int aEnd, std::string aMessage) {
    fileName = "";
    line = aLine;
    start = aStart;
    end = aEnd;
    message = std::move(aMessage);
    position = "";
}

Error::Error(Token& token, std::string aMessage) {
    fileName = "";
    line = token.line;
    start = token.start;
    end = token.end;
    message = std::move(aMessage);
    position = "";
}

void Error::printInfo() const {
    std::cerr<<generateReport()<<std::endl;
}

std::string Error::generateReport() const {
    std::string lineInfo = "[" + std::to_string(line) +
                           ":" + std::to_string(start) +
                           ":" + std::to_string(end) + "]";
    std::string messageInfo;
    if(position.empty()) {
        messageInfo = " -> " + message;
    }else{
        messageInfo = position + " -> " + message;
    }

    if(fileName.empty()) {
        return lineInfo.append(messageInfo);
    }

    return fileName + "\t" + lineInfo.append(messageInfo);
}

ErrorHandler::ErrorHandler() {
    hasError = false;
}

void ErrorHandler::report() {
    for(const auto& item : errorList) {
        item.printInfo();
    }
}

void ErrorHandler::addError(const Error& e) {
    errorList.push_back(e);
    hasError = true;
}

void ErrorHandler::clear() {
    errorList.clear();
    hasError = false;
}

int ErrorHandler::size() {
    return errorList.size();
}
