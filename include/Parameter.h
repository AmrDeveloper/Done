
#ifndef DONELANG_PARAMETER_H
#define DONELANG_PARAMETER_H

#include <utility>

#include "Token.h"

class Parameter {
public:
    Token name;
    Token type;
    MemoryType memoryType;
    bool isArrayType;
    Parameter(Token n, Token t, MemoryType pointer, bool isArray)
             : name(std::move(n)), type(std::move(t)), memoryType(pointer), isArrayType(isArray){}
};

#endif
