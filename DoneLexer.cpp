#include "include/DoneLexer.h"

#include <iostream>

DoneLexer::DoneLexer(const std::string& aSource, ErrorHandler& aErrorHandler)
: errorHandler(aErrorHandler){
    line = 1;
    start = 0;
    current = 0;
    source = aSource;

    reservedKeywords["if"]        = TokenType::IF;
    reservedKeywords["else"]      = TokenType::ELSE;
    reservedKeywords["else if"]   = TokenType::ELSE_IF;

    reservedKeywords["for"]       = TokenType::FOR;
    reservedKeywords["do"]        = TokenType::DO;
    reservedKeywords["while"]     = TokenType::WHILE;

    reservedKeywords["var"]       = TokenType::VAR;
    reservedKeywords["fun"]       = TokenType::FUN;
    reservedKeywords["return"]    = TokenType::RETURN;

    reservedKeywords["null"]      = TokenType::NIL;
    reservedKeywords["true"]      = TokenType::TRUE;
    reservedKeywords["false"]     = TokenType::FALSE;

    /*
    reservedKeywords["void"]      = TokenType::VOID;
    reservedKeywords["bool"]      = TokenType::BOOL;
    reservedKeywords["char"]      = TokenType::CHAT;
    reservedKeywords["short"]     = TokenType::SHORT;
    reservedKeywords["int"]       = TokenType::INT;
    reservedKeywords["double"]    = TokenType::DOUBLE;
    reservedKeywords["float"]     = TokenType::FLOAT;
     */

    reservedKeywords["enum"]      = TokenType::ENUM;
    reservedKeywords["struct"]    = TokenType::STRUCT;

    reservedKeywords["new"]       = TokenType::NEW;
    reservedKeywords["free"]      = TokenType::FREE;
}

std::vector<Token> DoneLexer::scanSourceCode() {
    while (!isAtEnd()) {
        start = current;
        scanAndAddToken();
    }
    tokens.emplace_back(TokenType::END_OF_FILE, "", "", line);
    return tokens;
}

char DoneLexer::advanceAndGetChar() {
    ++current;
    return source[current - 1];
}

void DoneLexer::scanAndAddToken() {
    const char c = advanceAndGetChar();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case ':':
            addToken(matchAndAdvance('=') ? TokenType::COLON_EQUAL
                                          : matchAndAdvance(':') ? TokenType::COLON_COLON : COLON);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '&':
            addToken(TokenType::ADDRESS);
            break;
        case '=':
            addToken(matchAndAdvance('=') ? TokenType::EQUAL_EQUAL
                                          : TokenType::EQUAL);
            break;
        case '<':
            addToken(matchAndAdvance('=') ? TokenType::LESS_EQUAL
                                          : TokenType::LESS);
            break;
        case '>':
            addToken(matchAndAdvance('=') ? TokenType::GREATER_EQUAL
                                          : TokenType::GREATER);
            break;
        case '/':
            if (matchAndAdvance('/')) {
                while (getCurrentChar() != '\n' && !isAtEnd())
                    advanceAndGetChar();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace
            break;
        case '\n':
            ++line;
            break;
        case '"':
            scanString();
            break;
        case '@' :
            scanPreprocessorLabel();
            break;
        default: {
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                scanIdentifier();
            } else {
                std::string errorMessage = "Unexpected character.";
                reportLexerError(errorMessage);
                break;
            }
        }
    }
}

void DoneLexer::scanPreprocessorLabel() {
    while (isAlphaNumeric(getCurrentChar())) advanceAndGetChar();
    const size_t identifierLength = current - start;
    const std::string label  = source.substr(start, identifierLength);

    current += identifierLength;
    start += identifierLength;

    if(label == "@LOAD") {
        while (getCurrentChar() != '\n' && !isAtEnd()) {
            advanceAndGetChar();
        }
        const size_t stringSize = current - start;
        const std::string stringLiteral = source.substr(start + 1, stringSize - 1);

        currentFile = stringLiteral;
        dependencyFilesStack.push(currentFile);

        return;
    }

    if(label == "@IGNORE") {
        line = line + 1;
        return;
    }

    if (label == "@END") {
        int filesSize = dependencyFilesStack.size();

        if (filesSize >= 2) {
            dependencyFilesStack.pop();
            currentFile = dependencyFilesStack.top();
            line = 1;
        }
    }
}

void DoneLexer::scanIdentifier() {
    while (isAlphaNumeric(getCurrentChar())) advanceAndGetChar();
    const size_t identifierLength = current - start;
    const std::string identifier  = source.substr(start, identifierLength);

    const bool isReservedKeyword = reservedKeywords.find(identifier) != reservedKeywords.end();

    if (isReservedKeyword) {
        addToken(reservedKeywords[identifier]);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

void DoneLexer::scanNumber() {
    while (isDigit(getCurrentChar())) {
        advanceAndGetChar();
    }

    if (getCurrentChar() == '.' && isDigit(getNextChar())) {
        advanceAndGetChar();
        while (isDigit(getCurrentChar())) {
            advanceAndGetChar();
        }
    }
    const size_t numberLength       = current - start;
    const std::string numberLiteral = source.substr(start, numberLength);
    addToken(TokenType::NUMBER, numberLiteral);
}

void DoneLexer::scanString() {
    while (getCurrentChar() != '"' && !isAtEnd()) {
        if (getCurrentChar() == '\n')
            ++line;
        advanceAndGetChar();
    }
    if (isAtEnd()) {
        std::string errorMessage = "Unterminated string.";
        reportLexerError(errorMessage);
        return;
    }
    advanceAndGetChar();
    const size_t stringSize = current - start;
    const std::string stringLiteral = source.substr(start + 1, stringSize - 2);
    addToken(TokenType::STRING, stringLiteral);
}

void DoneLexer::addToken(TokenType aTokenType, const std::string & value) {
    const size_t lexemeSize = current - start;
    const auto lexeme       = source.substr(start, lexemeSize);
    tokens.emplace_back(aTokenType, lexeme, value, line, start, current);
}

void DoneLexer::addToken(TokenType tokenType) {
   addToken(tokenType, "");
}

void DoneLexer::reportLexerError(std::string errorMessage) {
    std::string errorPosition = std::to_string(getCurrentChar());
    Error error(currentFile, line, start, current, std::move(errorMessage), errorPosition);
    errorHandler.addError(error);
}

bool DoneLexer::matchAndAdvance(char c) {
    if (isAtEnd()){
        return false;
    }
    if (source[current] != c) {
        return false;
    }
    ++current;
    return true;
}

char DoneLexer::getCurrentChar() {
    if (isAtEnd())
        return '\0';
    return source[current];
}

char DoneLexer::getNextChar() {
    if (current + 1 >= source.length())
        return '\0';
    return source[current + 1];
}

bool DoneLexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool DoneLexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool DoneLexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

bool DoneLexer::isAtEnd() {
    return current >= source.size();
}
