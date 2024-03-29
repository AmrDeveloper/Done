
#ifndef DONELANG_DONECOMPILER_H
#define DONELANG_DONECOMPILER_H

#include <string>

#include "CompilerOptions.h"

class DoneCompiler {
public:
  DoneCompiler(CompilerOptions *compilerOptions);
  void compile();
  void generateExecutable();
  void runExecutable();

private:
  CompilerOptions *compilerOptions;
};

#endif
