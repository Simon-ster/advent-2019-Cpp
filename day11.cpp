#include "common.hpp"
#include "intcode.cpp"

using Point = std::pair<int, int>;

class Robot {
   public:
    Memory program;
    Computer intcode;
};

void process(const String filename) {
    Point location{0, 0};

    std::cout << "Processing " << filename << std::endl;
    auto lines = getFileLines(filename);
    auto line = lines[0];
    Memory program;
    program.load(line);
    Computer computer;
    computer.load(program);
    std::map<Point, bool> car;
    std::map<Point, bool> painted;
    int direction = 0;
    int output = 1;   //run as 0 for p1
    int count = 0;
    int paint = 0;
    int locXMin = 0;
    int locXMax = 0;
    int locYMin = 0;
    int locYMax = 0;
    while (paint != -1) {
        int original = output;
        paint = computer.run(output);
        if (output != paint) {
            if (car[location] == false) {
                car[location] = true;
                count++;
            }
        }
        painted[location] = paint;
        output = paint;
        int right = computer.run(original);
        if (right) {
            direction = (direction + 1 + 4) % 4;
        } else {
            direction = (direction - 1 + 4) % 4;
        }

        switch (direction) {
            case 0:
                location.second++;
                break;
            case 1:
                location.first++;
                break;
            case 2:
                location.second--;
                break;
            case 3:
                location.first--;
                break;
        }
        locXMin = std::min(locXMin, location.first);
        locXMax = std::max(locXMax, location.first);
        locYMin = std::min(locYMin, location.second);
        locYMax = std::max(locYMax, location.second);

        output = painted[location];
    }

    for(int i = locYMax + 1; i > locYMin - 2; i--) {
        for (int j = locXMin - 1; j < locXMax + 1; j++) {
            Point test{j, i};
            if (painted[test] == false) {
                std::cout << '#';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << count << std::endl;
    // std::cout << locXMin << std::endl;
    // std::cout << locYMax << std::endl;
    // std::cout << locXMin << std::endl;
    // std::cout << locYMax << std::endl;
    ;
}

int main() {
    process("langton.txt");
    return 0;
}