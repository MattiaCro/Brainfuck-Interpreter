#include <iostream>
#include <string>

//ARGV -> fbint inputfile.txt
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "invalid arguments for this command";
        return 0;
    }
    int result;
#ifdef _WIN32
    std::string command = "interpreter ";
    command += argv[1];
    result = system(command.c_str());
#endif
    return result;
}