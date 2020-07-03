
#ifndef DONELANG_PARAMETER_H
#define DONELANG_PARAMETER_H

#include <utility>

#include "Token.h"

class Parameter {
public:
    Token name;
    Token type;
    Parameter(Token n, Token t) : name(std::move(n)), type(std::move(t)){}
};

#endif
