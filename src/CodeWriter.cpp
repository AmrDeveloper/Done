#include "../include/CodeWriter.h"

void CodeWriter::append(const std::string &line) { codeVector.push_back(line); }

void CodeWriter::appendLine(const std::string &line) {
  codeVector.push_back(line + "\n");
}

std::string CodeWriter::getSource() {
  std::string source;
  std::vector<std::string>::const_iterator line;
  for (line = codeVector.begin(); line != codeVector.end(); ++line) {
    source.append(*line);
  }
  return source;
}

void CodeWriter::clear() { codeVector.clear(); }

int CodeWriter::size() { return codeVector.size(); }
