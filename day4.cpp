#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

int getDigit(int &);
bool passTest(int[]);

int main() {
    freopen("password.txt", "r", stdin);
    std::string lower;
    getline(std::cin, lower);
    std::string upper;
    getline(std::cin, upper);
    int max = stoi(upper);
    std::stringstream ss;
    int number = stoi(lower);
    int temp = number;
    int count = 0;
    int array[6];

    while (number <= max) {
        temp = number;
        for (int i = 5; i >= 0; i--) {
            array[i] = getDigit(temp);
        }
        if (passTest(array)) {
            count++;
        }
        number++;
    }
    std::cout << count << std::endl;
    return 0;
}

int getDigit(int &number) {
    int digit = number % 10;
    number /= 10;
    return digit;
}

bool passTest(int array[]) {
    bool test = false;
    bool gotIt = false;
    for (int i = 0; i < 5; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
        if (array[i] == array[i + 1]) {
            test = true;
            if (i < 4) {
                if (array[i + 1] == array[i + 2]) {
                    test = false;
                }
            }
            if (i > 0) {
                if (array[i - 1] == array[i]) {
                    test = false;
                }
            }
            if (test) {
                gotIt = true;
            }
        }
    }

    return gotIt;
}