#ifndef DONELANG_CODEWRITER_H
#define DONELANG_CODEWRITER_H

#include <string>
#include <vector>

class CodeWriter {

private:
    std::vector<std::string> codeVector;

public:
    void append(const std::string&);
    void appendLine(const std::string&);
    std::string getSource();
    void clear();
    int size();
};

#endif

