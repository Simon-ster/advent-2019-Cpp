#include "common.hpp"
int main() {
    freopen("orbit.txt", "r", stdin);
    std::map<String, String> orbits;
    String orbitFirst;
    String orbitSecond;
    Vector<String> orbitList;
    while (getline(std::cin, orbitSecond, ')')) {
        getline(std::cin, orbitFirst);
        orbits[orbitFirst] = orbitSecond;
        orbitList.push_back(orbitFirst);
    }

    // for (unsigned int i = 0; i < orbitList.size(); i++) {
    //     std::cout <<  orbitList[i] <<std::endl;
    // }

    // part1
    {
        int part1 = 0;
        for (unsigned int i = 0; i < orbitList.size(); i++) {
            while (orbits[orbitList[i]] != "COM") {
                // String hello = orbits[orbitList[i]];
                orbitList[i] = orbits[orbitList[i]];
                part1++;
            }
            part1++;
        }
        std::cout << "Part1: " << part1 << std::endl;
    }

    {
        //int part2 = 0;
        Vector<String> myPath;
        Vector<String> sanPath;
        String you = "YOU";
        String santa = "SAN";
        while (you != "COM") {
            you = orbits[you];
            myPath.push_back(you);
        }
        while (santa != "COM") {
            santa = orbits[santa];
            sanPath.push_back(santa);
        }
        int size = std::max(sanPath.size(), myPath.size());
        int part2;
        int j = 1;
        int i = 1;
        for (int k = 0; k < size; k++) {
            String hello = sanPath[sanPath.size()-i];
            String bye = myPath[myPath.size()-j];
            
            if (sanPath[sanPath.size()-i] != myPath[myPath.size()-j]) {
                break;
            }
            else {
                j++;
                i++;
            }
            int sanTot = sanPath.size()- i + 1;
            int myTot = myPath.size() - j + 1;
            part2 = sanTot + myTot;
        }
        std::cout << "Part 2: " << part2 << std::endl;

        // for (unsigned int i = 0; i < myPath.size(); i++) {
        //     std::cout << myPath[i] << std::endl;
        // }
        // for (unsigned int i = 0; i < sanPath.size(); i++) {
        //     std::cout << sanPath[i] << std::endl;
        // }
    }

    return 0;
}
