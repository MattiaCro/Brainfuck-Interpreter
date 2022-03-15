#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "brainfuck.hpp"

VString readRawCode(const char* fileName) {
    VString vector;
    InputStrm ifs(fileName);
    str check;
    while (ifs >> check) {
        vector.push_back(check);
    }
    return vector;
}

VChar getFinalCode(VString& rawCode, int& checkBrackets) {
    VChar code;
    checkBrackets = 0;
    for (int nWord = 0; nWord < rawCode.size(); ++nWord) {
        for (int nChar = 0; nChar < rawCode[nWord].length(); ++nChar) {
            auto charat = rawCode[nWord][nChar];
            if (std::find(COMMANDS_V.begin(), COMMANDS_V.end(), charat) != COMMANDS_V.end()) {
                //IF THE CHAR IS NOT FOUND YOU JUST REMOVE IT
                code.push_back(charat);
                if (charat == '[') { 
                    ++checkBrackets; 
                }
                else if (charat == ']') { 
                    --checkBrackets; 
                }
            }
        }   
    }
    return code;
}

int interpretateCode(const VChar& code) {
    VChar memory(1, 0);
    int pos = 0;
    int res;
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
    return res;
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
