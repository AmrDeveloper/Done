
#ifndef DONELANG_PARAMETER_H
#define DONELANG_PARAMETER_H

#include <utility>

#include "Token.h"

class Parameter {
public:
    Token name;
    Token type;
    bool isPointer;
    Parameter(Token n, Token t, bool pointer)
             : name(std::move(n)), type(std::move(t)), isPointer(pointer){}
};

#endif
