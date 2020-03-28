#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int doStuff(std::vector<int>&, int&);

int main() {
    std::ifstream ifs;
    std::string fileName = "test.txt";

    std::vector<int> vec;
    ifs.open(fileName);
    if (ifs.fail()) {
        std::cout << "Cannot open the file." << std::endl;
        return 1;
    }
    std::string input_str;
    char ch;
    while (ifs >> ch) {
        input_str += ch;
    }

    std::stringstream ss(input_str);
    for (int j; ss >> j;) {
        vec.push_back(j);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
    ifs.close();
    int i = 0;
    int opcode = 0;
    while (opcode != 99) {
        opcode = doStuff(vec, i);
    }

    for (unsigned int j = 0; j < vec.size(); j++) {
        std::cout << vec[j] << ", ";
    }
    return 0;
}

int doStuff(std::vector<int>& vec, int& i) {
    std::map<char, int> info;
    int instruction;
    std::string stuff = std::to_string(vec[i]);
    char array[] = {'A', 'B', 'C', 'D', 'E'};
    while (stuff.size() != 5) {
        stuff = "0" + stuff;
    }
    for (int j = 4; j >= 0; j--) {
        info[array[j]] = int(stuff[j]) - 48;
    }
    int opcode = (info['D'] * 10 + info['E']);
    int firstMode = info['C'];
    int secondMode = info['B'];
    int thirdMode = info['A'];
    int index1 = vec[i + 1];
    int index2 = vec[i + 2];
    int index3 = vec[i + 3];
    if (firstMode == 1) {
        index1 = i + 1;
    }
    if (secondMode == 1) {
        index2 = i + 2;
    }
    if (thirdMode == 1) {
        index3 = i + 3;
    }

    if (opcode == 1) {
        vec[index3] = vec[index1] + vec[index2];
        int bloop = vec[index3];
        i += 4;
    } else if (opcode == 2) {
        vec[index3] = vec[index1] * vec[index2];
        int bloop = vec[index3];
        i += 4;
    } else if (opcode == 3) {
        std::cin >> instruction;
        vec[index1] = instruction;
        int bloop = vec[index1];
        i += 2;
    } else if (opcode == 4) {
        std::cout << vec[index1];
        i += 2;
    } else if (opcode == 5) {
        // jump if true
        if (vec[index1] != 0) {
            i = vec[index2];
        }
        else {
            i+=3;
        }
    } else if (opcode == 6) {
        if (vec[index1] == 0) {
            i = vec[index2];
        }
        else {
            i+=3;
        }
    } else if (opcode == 7) {
        if (vec[index1] < vec[index2]) {
            vec[index3] = 1;
        } else {
            vec[index3] = 0;
        }
        i+=4;
    } else if (opcode == 8) {
        if (vec[index1] == vec[index2]) {
            vec[index3] = 1;
        } else {
            vec[index3] = 0;
        }
        i+=4;
    } else {
        std::cout << "You shouldn't be here" << std::endl;
    }
    return opcode;
}