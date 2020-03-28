#include "common.hpp"

// using Program = Vector<int>;

struct Program : Vector<int> {
    void load(const String line) {
        auto inputs = splitString(line, ',');

        clear();

        for (auto &input : inputs) {
            push_back(std::stoi(input));
        }
    }
};
struct Computer {
    Program program;
    int cursor{0};
    bool recFirstInput{false};

    void load(const Program &pgrm) {
        program = pgrm;
        cursor = 0;
        recFirstInput = false;
    }

    int run(const int signal, const int setting) {
        while (cursor < program.size()) {
            auto value = program[cursor];
            std::map<char, int> info;
            char array[] = {'A', 'B', 'C', 'D', 'E'};
            String valueStr = std::to_string(value);

            while (valueStr.size() < 5) {
                valueStr = "0" + valueStr;
            }
            for (int j = 4; j >= 0; j--) {
                info[array[j]] = int(valueStr[j]) - 48;
            }
            int opcode = (info['D'] * 10 + info['E']);
            int firstMode = info['C'];
            int secondMode = info['B'];
            int thirdMode = info['A'];
            int index1 = program[cursor + 1];
            int index2 = program[cursor + 2];
            int index3 = program[cursor + 3];

            if (firstMode == 1) {
                index1 = cursor + 1;
            }
            if (secondMode == 1) {
                index2 = cursor + 2;
            }
            if (thirdMode == 1) {
                index3 = cursor + 3;
            }

            if (opcode == 1) {
                program[index3] = program[index1] + program[index2];
                cursor += 4;
            } else if (opcode == 2) {
                program[index3] = program[index1] * program[index2];
                cursor += 4;
            } else if (opcode == 3) {
                if (!recFirstInput) {
                    program[index1] = signal;
                    recFirstInput = true;
                } else {
                    program[index1] = setting;
                }
                cursor += 2;
            } else if (opcode == 4) {
                cursor += 2;
                return program[index1];
            } else if (opcode == 5) {
                // jump if true
                if (program[index1] != 0) {
                    cursor = program[index2];
                } else {
                    cursor += 3;
                }
            } else if (opcode == 6) {
                if (program[index1] == 0) {
                    cursor = program[index2];
                } else {
                    cursor += 3;
                }
            } else if (opcode == 7) {
                if (program[index1] < program[index2]) {
                    program[index3] = 1;
                } else {
                    program[index3] = 0;
                }
                cursor += 4;
            } else if (opcode == 8) {
                if (program[index1] == program[index2]) {
                    program[index3] = 1;
                } else {
                    program[index3] = 0;
                }
                cursor += 4;
            } else if (opcode == 99) {
                return -1;
            } else {
                std::cout << "You shouldn't be here" << std::endl;
                cursor++;
            }
            cursor %= program.size();
        }
        return -1;
    }
};

struct Ship {
    Computer amplifiers[5];
    Program program;

    void load(const String line) { program.load(line); }

    void reset() {
        for (auto &amp : amplifiers) {
            amp.load(program);
        }
    }

    int run(const Array<int, 5> &setup) {
        reset();
        int output = 0;
        for (int i = 0; i < setup.size(); i++) {
            output = amplifiers[i].run(setup[i], output);
        }
        return output;
    }

    int run2(const Array<int, 5> &setup) {
        reset();
        int output = 0;
        int lastoutput = 0;
        while (true) {
            for (int i = 0; i < setup.size(); i++) {
                int j = amplifiers[i].run(setup[i], output);
                if (j == -1) {
                    return lastoutput;
                }
                output = j;
            }
            lastoutput = output;
        }
        return output;
    }
};

void process(const String filename) {
    std::cout << "Processing " << filename << std::endl;
    auto lines = getFileLines(filename);
    auto line = lines[0];
    Ship ship;
    ship.load(line);

    {
        int max = 0;

        Array<int, 5> options = {0, 1, 2, 3, 4};
        
        do {
            int r = ship.run(options);
            max = std::max(r, max);
        } while (std::next_permutation(options.begin(), options.end()));
        std::cout << '(' << max;
    }
    {
        int max = 0;
        Array<int, 5> options2 = {5, 6, 7, 8, 9};
        do {
            int r = ship.run2(options2);
            max = std::max(r, max);

        } while (std::next_permutation(options2.begin(), options2.end()));
        std::cout << ", " << max << ")" << std::endl;
        
    }
}

int main() {
    process("thruster.txt");
    return 0;
}