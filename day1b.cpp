#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int calculate(int);

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
    while (ifs >> val) {
        modules.push_back(val);
    }

    int sum = 0;
    int number;
    for (int i = 0; i < modules.size(); i++) {
        number = modules[i];
        sum += calculate(number);
    }
    ifs.close();
    std::cout << sum << std::endl;
    /* code */
    return 0;
}

int calculate(int number) {
    int sum = 0;
    while (number > 0) {
        number /= 3;
        number -= 2;
        if (number > 0) {
            sum += number;
        }
    }
    return sum;
}