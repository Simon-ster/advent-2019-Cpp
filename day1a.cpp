#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int main(int argc, char const *argv[]) {
    std::ifstream ifs;
    std::string fileName = "module.txt";

    std::vector<int> modules;
    ifs.open(fileName);
    if (ifs.fail()) {
        std::cout << "Cannot open the file." << std::endl;
        return 1;
    }
    int val;
    while (!ifs.eof()) {;
        modules.push_back(val);
    }

    int total = 0;
    int number;
    for (int i = 0; i < modules.size(); i++) {
        number = modules[i];
        number /= 3;
        number -= 2;
        total += number;
    }
    ifs.close();
    std::cout << total << std::endl;
    /* code */
    return 0;
}