#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
    std::stringstream  ss(input_str);
    int j;
    for (int j; ss >> j;) {
        modules.push_back(j);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    int sum = 0;
    int i = 0;
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
    ifs.close();
    for (int i = 0; i < modules.size(); i++) {
        std::cout << modules[i] << ", ";
    }
    /* code */
    return 0;
}
