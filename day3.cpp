#include <stdio.h>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
    freopen("wires.txt", "r", stdin);
    //std::map<std::pair<int, int>, bool> visitedPath;
    std::map<std::pair<int, int>, int> visitedPath;
    std::string wirePath;
    int minDistance = INT_MAX;
    // Read path
    while (getline(std::cin, wirePath)) {
        std::map<std::pair<int, int>, bool> currentPath;
        std::stringstream ss(wirePath);
        std::string move;
        std::pair<int, int> position = {0, 0};
        int totalDistance = 0;
        // Read moves
        while (getline(ss, move, ',')) {
            char direction = move.front();
            move.erase(move.begin());
            int distance = stoi(move);
            while (distance--) {
                totalDistance++;
                if (direction == 'U') {
                    position.first++;
                } else if (direction == 'D') {
                    position.first--;
                } else if (direction == 'R') {
                    position.second++;
                } else {  // direction == 'L'
                    position.second--;
                }
                /*
                if (visitedPath[position] && !currentPath[position]) {
                    minDistance =
                        std::min(minDistance, abs(position.first) + abs(position.second));
                }
                */
                if (visitedPath[position] != 0 && !currentPath[position]) {
                    minDistance = std::min(minDistance, totalDistance + visitedPath[position]);
                }
                currentPath[position] = true;
                visitedPath[position] = totalDistance;
                //visitedPath[position] = true;
            }
        }
    }
    std::cout << minDistance << std::endl;

    return 0;
}