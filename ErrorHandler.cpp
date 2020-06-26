#include "include/ErrorHandler.h"
#include <iostream>

Error::Error(int aLine, int aStart, int aEnd,
        std::string aMessage, std::string aPosition) {
    line = aLine;
    start = aStart;
    end = aEnd;
    message = std::move(aMessage);
    position = std::move(aPosition);
}


void Error::printInfo() const {
    std::cerr<<generateReport()<<std::endl;
}

std::string Error::generateReport() const {
    std::string lineInfo = "[" + std::to_string(line) +
                           ":" + std::to_string(start) +
                           ":" + std::to_string(end) + "]";
    std::string messageInfo = position + " -> " + message;
    return lineInfo.append(messageInfo);
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
