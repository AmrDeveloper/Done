#include "include/DoneCompiler.h"

int main() {
    std::string mainFile = "Enume.done";
    std::string projectPath = "../examples/";

    DoneCompiler doneCompiler;
    doneCompiler.setOutputCFileName("Enume.c");
    doneCompiler.compile(mainFile, projectPath);
    return EXIT_SUCCESS;
}
