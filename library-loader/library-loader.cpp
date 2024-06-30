#include <windows.h>
#include <iostream>

void showUsage() {
    std::cout << "Usage: loader.exe -f <DLL_Name>\n";
    std::cout << "Options:\n";
    std::cout << "  -f    Specify the DLL file to load\n";
    std::cout << "  -h    Display this help message\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        showUsage();
        return 1;
    }

    std::string arg1 = argv[1];
    std::string filePath = argv[2];

    if (arg1 == "-h") {
        showUsage();
        return 0;
    }
    else if (arg1 != "-f") {
        showUsage();
        return 1;
    }

    HINSTANCE hDll = LoadLibraryA(filePath.c_str());
    if (hDll == NULL) {
        std::cerr << "Something went wrong" << std::endl;
        return 1;
    }

    std::cout << "Loaded" << std::endl;

    FreeLibrary(hDll);
    return 0;
}