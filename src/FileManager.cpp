#include <filesystem>
#include <fstream>

#include "../include/FileManager.h"

bool writeFileContent(std::string path, std::string content) {
  std::ofstream sourceFile(path);
  if (sourceFile.is_open()) {
    sourceFile << content;
    sourceFile.close();
    return true;
  }
  return false;
}

std::string readFileContent(std::string path) {
  std::streampos size;
  char *readedText;
  std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    readedText = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(readedText, size);
    file.close();
    return readedText;
  }
  return new char[0];
}

std::string getFileName(std::string path) {
  std::filesystem::path fsPath = {path};
  return fsPath.filename();
}

std::string getFileExtension(std::string path) {
  std::filesystem::path fsPath = {path};
  return fsPath.extension();
}

std::string getFileParentPath(std::string path) {
  std::filesystem::path fsPath = {path};
  return fsPath.parent_path();
}