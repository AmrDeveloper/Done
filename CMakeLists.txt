cmake_minimum_required(VERSION 3.16)
project(DoneLang)

set(CMAKE_CXX_STANDARD 11)

add_executable(DoneLang main.cpp include/TokenType.h include/CodeWriter.h CodeWriter.cpp include/DoneLexer.h include/Token.h Token.cpp DoneLexer.cpp "include/ErrorHandler.h" ErrorHandler.cpp include/DoneParser.h DoneParser.cpp include/Visitor.h include/Preprocessor.h Preprocessor.cpp)