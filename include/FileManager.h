#ifndef DONELANG_FILEMANAGER_H
#define DONELANG_FILEMANAGER_H

#include <iostream>

bool writeFileContent(std::string path, std::string content);

std::string readFileContent(std::string path);

std::string getFileName(std::string path);

std::string getFileExtension(std::string path);

std::string getFileParentPath(std::string path);

#endif