#include "common.hpp"
#include "intcode.cpp"
using Point = std::pair<int, int>;

void process(const String filename) {
    std::cout << "Processing " << filename << std::endl;
    auto lines = getFileLines(filename);
    auto line = lines[0];
    Memory program;
    program.load(line);
    Computer computer;
    program[0] = 2;
    computer.load(program);
    

    int maxX = 0;
    int maxY = 0;
    int input = 0;  // set to 2 to put in 2 quarters;
    int currentScore = 0;
    int xBall = 0;
    int xJoy = 0;
    int count = 0;

    std::map<Point, int> m;
    Point test;
    int output = 0;
    Point location;
    while (true) {
        location.first = computer.run(input);
        if (location.first == -99) {
            break;
        }
        location.second = computer.run(input);
        output = computer.run(input);
        m[location] = output;
        if (location.first != -1) {
            if (output == 4) {
                xBall = location.first;
            }
            if (output == 3) {
                xJoy = location.first;
            }
        } else {
            if (location.second == 0) {
                currentScore = output;
            }
        }
        maxX = std::max(location.first, maxX);
        maxY = std::max(location.second, maxY);
        if (xBall < xJoy) {
            input = -1;
        } else if (xBall > xJoy) {
            input = 1;
        } else{
            input = 0;
        }
    }
    count = 0;
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX + 1; j++) {
            test.first = j;
            test.second = i;
            if (m[test] == 2) {
                count++;
            }
        }
    }

    std::cout << "Part 2: " << currentScore << std::endl;
}
int main() {
    process("arcade.txt");
    return 0;
}
