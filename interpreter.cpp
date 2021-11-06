#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "bf\brainfuck.hpp"

int main(int argc, char* argv[]) {
    //NO GUARD ABOUT ARGC, ALREADY IN MAIN PROGRAM
    VString rawCode = readArrayOfRawCodeFromInputFile(argv[1]);
    int checkBraces;
    VChar code = getFinalCode(rawCode, checkBraces);
    if (checkBraces != 0) {
        std::cerr << "error in opening or closing loop";
        return 0;
    }
    int result = interpretateCode(code);
    return result;
}

/*
    0- array of infinite cells -> vector [0][1][2][3]----->
    1- "+" -> increase the value of the cell by one
    2- "-" -> decrease the value of the cell by one
    3- ">" -> +1 on the position of the pointer
    4- "<" -> -1 on the position of the pointer
    5- "[" -> start of a loop body, until the current cell value is 0 ---->CHECK FOR START AND END OF THE LOOP
    6- "]" -> end of the loop body
    7- "," -> ask in input the cell value
    8- "." -> print the cell value

    VECTOR WITH SIZE 1 CREATED.

*/