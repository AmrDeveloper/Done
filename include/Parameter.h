
#ifndef DONELANG_PARAMETER_H
#define DONELANG_PARAMETER_H

#include <utility>

#include "Token.h"

class Parameter {
public:
    Token name;
    Token type;
    MemoryType memoryType;
    Parameter(Token n, Token t, MemoryType pointer)
             : name(std::move(n)), type(std::move(t)), memoryType(pointer){}
};

#endif
