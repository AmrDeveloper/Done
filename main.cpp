#include "include/DoneCompiler.h"

int main() {
    std::string mainFile = "Source2.done";
    std::string projectPath = "../examples/";

    DoneCompiler doneCompiler;
    doneCompiler.compile(mainFile, projectPath);
    return EXIT_SUCCESS;
}
