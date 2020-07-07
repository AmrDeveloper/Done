
#ifndef DONELANG_ERRORHANDLER_H
#define DONELANG_ERRORHANDLER_H

#include <string>
#include <vector>

#include "Token.h"

class Error {
public:
   Error(std::string file, int line, int start, int end, std::string message, std::string position);
   Error(int line, int start, int end, std::string message);
   Error(Token &token, std::string message);
   int line;
   int start;
   int end;
   std::string fileName;
   std::string message;
   std::string position;
   void printInfo() const;
   std::string generateReport() const;
};

class ErrorHandler {
public:
    ErrorHandler();
    void report();
    void addError(const Error& error);
    void clear();
    int  size();
    bool hasError;
private:
    std::vector<Error> errorList;
};

#endif
