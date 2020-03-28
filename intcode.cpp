#include "common.hpp"

// using Program = Vector<int>;
struct Memory : Map<long long int, long long int> {
    void load(const String line) {
        auto inputs = splitString(line, ',');

        clear();

        long long int i = 0;
        for (auto &input : inputs) {
            (*this)[i] = std::stoll(input);
            i++;
        }
    }
};

struct Computer {
    Memory program;
    unsigned int cursor{0};
    bool recFirstInput{false};
    long long int relativeBase;

    void load(const Memory &pgrm) {
        program = pgrm;
        cursor = 0;
        //recFirstInput = false;
        relativeBase = 0;
    }

    long long run(const int signal, const int setting = 0) {
        while (cursor < program.size()) {
            long long value = program[cursor];
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
            long long int index1 = program[cursor + 1];
            long long int index2 = program[cursor + 2];
            long long int index3 = program[cursor + 3];
            

            if (firstMode == 1) {
                index1 = cursor + 1;
            } else if (firstMode == 2) {
                index1 += relativeBase;
            }
            if (secondMode == 1) {
                index2 = cursor + 2;
            } else if (secondMode == 2) {
                index2 += relativeBase;
            }
            if (thirdMode == 1) {
                index3 = cursor + 3;
            } else if (thirdMode == 2) {
                index3 += relativeBase;
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
                } else {
                    program[index1] = setting;
                }
                cursor += 2;
            } else if (opcode == 4) {
                cursor += 2;
                return program[index1];
            } else if (opcode == 5) {
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
            } else if (opcode == 9) {
                relativeBase += program[index1];
                cursor += 2;
            } else if (opcode == 99) {
                return -99;
            } else {
                std::cout << "You shouldn't be here" << std::endl;
                cursor++;
            }
            cursor %= program.size();
        }
        return -99;
    }
};