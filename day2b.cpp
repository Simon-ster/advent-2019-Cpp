#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void test(int,int,std::vector<int>);

int main() {
    std::ifstream ifs;
    std::string fileName = "1202.txt";

    std::vector<int> modules;
    ifs.open(fileName);
    if (ifs.fail()) {
        std::cout << "Cannot open the file." << std::endl;
        return 1;
    }

    int val;
    std::string input_str;
    char ch;
    while (ifs >> ch) {
        input_str += ch;
    }
    ifs.close();
    std::stringstream  ss(input_str);
    int j;
    for (int j; ss >> j;) {
        modules.push_back(j);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    int noun = 0;
    int verb = 0;
    int p = 0;
    for (int k = 0; k < 99; k++) {
        for (int l = 0; l < 99; l++) {
            test(noun, verb, modules);
            verb++;
        }
        verb = 0;
        noun++;
    }
    /* code */
    return 0;
}

void test(int noun, int verb, std::vector<int> modules) {
    int i = 0;
    modules[1] = noun;
    modules[2] = verb;
    while (modules[i] != 99) {
        int index1 = modules[i + 1];
        int index2 = modules[i + 2];
        int index3 = modules[i + 3];
        if (modules[i] == 1) {
            modules[index3] = modules[index1] + modules[index2];
            i += 4;
        } else if (modules[i] == 2) {
            modules[index3] = modules[index1] * modules[index2];
            i += 4;
        }
        else {
            std::cout << "You shouldn't be here" << std::endl;
        }
    }
    if (modules[0] == 19690720) {
        std::cout << noun << ", " << verb << std::endl;
    }
}