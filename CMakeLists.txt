cmake_minimum_required(VERSION 3.16)
project(DoneLang)

set(CMAKE_CXX_STANDARD 11)

add_executable(DoneLang main.cpp include/TokenType.h include/CodeWriter.h CodeWriter.cpp include/DoneLexer.h include/Token.h Token.cpp DoneLexer.cpp include/ErrorHandler.h ErrorHandler.cpp include/DoneParser.h DoneParser.cpp include/Preprocessor.h Preprocessor.cpp include/ExpressionVisitor.h include/Expression.h include/Statement.h include/StatementVisitor.h include/EnumStatement.h include/CodeGenerator.h CodeGenerator.cpp include/VarStatement.h include/AssignExpression.h include/LiteralExpression.h include/StructStatement.h include/ExpressionStatement.h include/BlockStatement.h include/FunctionStatement.h include/Parameter.h include/IfStatement.h include/CallExpression.h include/VariableExpression.h)