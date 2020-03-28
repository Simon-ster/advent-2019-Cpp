#include "common.hpp"

struct Moon {
   private:
    std::array<int, 3> moonPos, moonVel;

   public:
    Moon(int x, int y, int z) : moonPos{x, y, z}, moonVel{0, 0, 0} {}
    std::array<int, 3> &getPosition() { return moonPos; }
    std::array<int, 3> &getVelocity() { return moonVel; }
    void step() {
        for (int i = 0; i < 3; i++) {
            moonPos[i] += moonVel[i];
        }
    }
};

void calcGrav(Moon &moon1, Moon &moon2, int position) {
    if (moon1.getPosition()[position] > moon2.getPosition()[position]) {
        moon1.getVelocity()[position]--;
        moon2.getVelocity()[position]++;
    } else if (moon1.getPosition()[position] < moon2.getPosition()[position]) {
        moon1.getVelocity()[position]++;
        moon2.getVelocity()[position]--;
    } else {
        // value stays zero
    }
}

bool check(Moon &initial, Moon &current, int stop) {
    if (initial.getPosition()[stop] == current.getPosition()[stop]) {
        return true;
    }
    else {
        return false;
    }
}

void compare(std::vector<Moon> &moons) {
    for (int i = 0; i < moons.size(); i++) {
        for (int j = i + 1; j < moons.size(); j++) {
            calcGrav(moons[i], moons[j], 0);
            calcGrav(moons[i], moons[j], 1);
            calcGrav(moons[i], moons[j], 2);
        }
        moons[i].step();
    }
}

bool zero(int a, int b, int c, int d) {
    if(a == 0 && b == 0 && c == 0 && d == 0) {
        return true;
    }
    else {
        return false;
    }
}

void compare2(std::vector<Moon> &initial, std::vector<Moon> &current, std::array<int, 3> &stops, int &step) {
    for(int i = 0; i < stops.size(); i++) {
        bool first = check(initial[0], current[0], i);
        bool second = check(initial[1], current[1], i);
        bool third = check(initial[2], current[2], i);
        if (first && second && third) {
            if(zero(current[0].getVelocity()[i], current[1].getVelocity()[i], current[2].getVelocity()[i], current[3].getVelocity()[i])) {
                if(!stops[i]) {
                    stops[i] = step;
                }    
            }
        }
    }
    step++;
}

void calcE(std::vector<Moon> &moons, std::vector<int> &PE,
           std::vector<int> &KE) {
    PE.clear();
    KE.clear();
    for (int i = 0; i < moons.size(); i++) {
        int p = std::abs(moons[i].getPosition()[0]) +
                std::abs(moons[i].getPosition()[1]) +
                std::abs(moons[i].getPosition()[2]);
        PE.push_back(p);
        int k = std::abs(moons[i].getVelocity()[0]) +
                std::abs(moons[i].getVelocity()[1]) +
                std::abs(moons[i].getVelocity()[2]);
        KE.push_back(k);
    }
}
int main() {
    Moon moon1(-16, -1, -12);
    Moon moon2(0, -4, -17);
    Moon moon3(-11, 11, 0);
    Moon moon4(2, 2, -6);
    // Moon moon1(-1, 0, 2);
    // Moon moon2(2, -10, -7);
    // Moon moon3(4, -8, 8);
    // Moon moon4(3, 5, -1);
    std::vector<int> PE;
    std::vector<int> KE;
    int total = 0;

    std::vector<Moon> moons = {moon1, moon2, moon3, moon4};
    std::vector<Moon> initialMoons = moons;
    std::array<int, 3> stop = {0, 0, 0};
    int count = 1;
    while (!stop[0] || !stop[1] || !stop[2]) {
        compare(moons);
        if (count == 1000) {
            calcE(moons, PE, KE);
            for (int i = 0; i < 4; i++) {
                total += (PE[i] * KE[i]);
            }
        }
        compare2(initialMoons, moons, stop, count);
    }
    std::cout << "Part 1: " << total << std::endl;
    std::cout << "Part 2: " << std::lcm(std::lcm((std::int64_t)stop[0], (std::int64_t)stop[1]), (std::int64_t)stop[2]) << std::endl;
    return 0;
}