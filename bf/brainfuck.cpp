#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "brainfuck.hpp"

VString readArrayOfRawCodeFromInputFile(const char* fileName) {
    VString vector;
    InputStrm ifs;
    ifs.open(fileName);
    while (!ifs.eof()) {
        str check;
        ifs >> check;
        vector.push_back(check);
    }
    ifs.close();
    return vector;
}

VChar getFinalCode(VString& rawCode, int& checkBrackets) {
    VChar code;
    checkBrackets = 0;
    for (int nWord = 0; nWord < rawCode.size(); ++nWord) {
        for (int nChar = 0; nChar < rawCode[nWord].length(); ++nChar) { //loop through every character of every string in the file
            auto charat = rawCode[nWord][nChar]; //(didn't know if I need a pointer)
            if (std::find(COMMANDS_V.begin(), COMMANDS_V.end(), charat) != COMMANDS_V.end()) { //check the char is in the command
                //push it in the final code (char vector)
                code.push_back(charat);
                if (charat == '[') {
                    ++checkBrackets;
                }
                else if (charat == ']') {
                    --checkBrackets;
                }
                //check brackets, if the sum of closing and opening ones
                //is equal to 0 there's no errors, otherwise there's an error
            }
        }   
    }
    return code;
}

int interpretateCode(const VChar& code) {
    VChar memory(1, 0); //treated as a VInt
    int pos = 0;
    VInt loopPositions;
    for (int i = 0; i < code.size(); ++i) {
        switch (code[i]) {
            case '+': //++CURRENTCELL
                ++memory[pos];
                break;
            case '-': //++CURRENTCELL
                --memory[pos];
                break;
            case '>': //MOVE NEXT CELL
                ++pos;
                if (memory.size() - 1 < pos) {
                    memory.push_back(0);
                }
                break;
            case '<': //MOVE PREVIOUS CELL
                if (pos > 0) {
                    --pos;
                    break;
                }
                else {
                    std::cerr << "index out of bound";
                    return 0;
                }
            case '[': //START LOOP
                if (memory[pos] != 0) {
                    loopPositions.push_back(i);
                }
                else {
                    ++i; //skip current bracket and start ignore at one
                    for (int ignore = 1; i < code.size() && ignore != 0; ++i) {
                        if (code[i] == ']') {
                            --ignore;
                        }
                        else if (code[i] == '[') {
                            ++ignore;
                        }
                    }
                    --i; //move back and point at the close brackt
                }
                break;
            case ']': //ENDLOOP
                if (memory[pos] != 0) {
                    i = loopPositions.back();
                }
                else {
                    loopPositions.pop_back();
                }
                break;
            case '.': //PRINT AS CHAR
                std::cout << (char)memory[pos];
                break;
            case ',':
                std::cin >> memory[pos];
                break;
        }
    }
    //END CODE
    printAllCells(memory, pos);
    return 1;
}

void printAllCells(const VChar& memory, int pos) {
    std::cout << "\n\n==>";
    for (int i = 0; i < memory.size(); ++i) {
        if (i == pos) {
            std::cout << "[" << (int)memory[i] << "] ";
        }
        else {
            std::cout << (int)memory[i] << " ";
        }
    }
}