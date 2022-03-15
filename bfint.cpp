#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "bf\brainfuck.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "invalid arguments for this command";
        return 1;
    }
    VString rawCode = readRawCode(argv[1]);
    int checkBraces;
    VChar code = getFinalCode(rawCode, checkBraces);
    if (checkBraces != 0) {
        std::cerr << "error in opening or closing loop";
        return 0;
    }
    int result = interpretateCode(code);
    return result;
}
