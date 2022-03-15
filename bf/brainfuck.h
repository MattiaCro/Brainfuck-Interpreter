#ifndef BRAINFUCK_HPP
#define BRAINFUCK_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

//ALL UPPER 'V' STANDS FOR STD::VECTOR<T>
using str = std::string;
using VString = std::vector<str>;
using VChar = std::vector<char>;
using VInt = std::vector<int>;
using InputStrm = std::ifstream;
const VChar COMMANDS_V {'+', '-', '>', '<', '[', ']', ',', '.'};

int interpretateCode(const VChar&);
VString readRawCode(const char*);
VChar getFinalCode(VString&, int&);
void printAllCells(const VChar&, int);

#endif
