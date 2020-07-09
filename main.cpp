#include "include/DoneCompiler.h"
#include <iostream>
#include <algorithm>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else

#include <unistd.h>

#define GetCurrentDir getcwd
#endif

#define COMPILE_DEBUG_MODE

std::string getCurrentDirectoryPath() {
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
        return "";
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    std::string path(cCurrentPath);
    std::replace( path.begin(), path.end(), '\\', '/');
    path.append("/");
    return path;
}

int main(int argc, char* argv[]) {
#ifdef COMPILE_DEBUG_MODE
    DoneCompiler doneCompiler;
    std::string mainFile = "Enume.done";
    std::string projectPath = "../examples/";
    doneCompiler.compile(mainFile, projectPath);
    //doneCompiler.generateExecutable();
    exit(EXIT_SUCCESS);
#endif
    if(argc < 2) {
        std::cout<<"Must include at last main file name";
        return EXIT_FAILURE;
    }
    else{
        DoneCompiler doneCompiler;
        std::string mainFile;
        std::string projectPath = getCurrentDirectoryPath();

        if(argc > 1) {
            mainFile = argv[1];
        }
        if(argc > 2) {
            std::string cOutputName = argv[2];
            if(cOutputName.length() >= 2) {
                std::string extension = cOutputName.substr(cOutputName.size() - 2);
                if(extension != ".c") {
                    cOutputName.append(".c");
                }
            }
            doneCompiler.setOutputCFileName(cOutputName);
        }
        if(argc > 3) {
            std::string executableOutputName = argv[3];
            doneCompiler.setExecutableFileName(executableOutputName);
        }

        doneCompiler.compile(mainFile, projectPath);
        doneCompiler.generateExecutable();
        //doneCompiler.runExecutable();
    }
    return EXIT_SUCCESS;
}
