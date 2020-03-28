#include "common.hpp"
#define PI 3.14159265

class Asteroid {
    double angle;
    double distance;

   public:
    int xCoord;
    int yCoord;
    Asteroid(int x, int y) {
        xCoord = x;
        yCoord = y;
        distance = 0;
        angle = 0;
    }
    void SetAngleDistance(int x, int y) {
        int xDif = x - xCoord;
        int yDif = yCoord - y;

        double p = std::pow(xDif, 2) + std::pow(yDif, 2);
        distance = std::sqrt(p);
        // int distance = r;
        double a = atan2(yDif, xDif) * 180 / PI;
        if (a < 0) {
            a += 360;
        }
        angle = a;
    }
    double getAngle() { return angle; }
    double getDist() { return distance; }
};
// hello

int main() {
    freopen("asteroid.txt", "r", stdin);
    std::map<int, std::map<int, char>> m;  // m(x, y)
    String line;
    std::vector<Asteroid> ast;
    // std::vector<Asteroid> copy;
    std::map<int, std::map<int, std::vector<Asteroid>>> track;
    int p = 0;
    int numAst = 0;
    int xBest = 0;
    int yBest = 0;

    while (getline(std::cin, line)) {
        for (unsigned int i = 0; i < line.size(); i++) {
            m[p][i] = line[i];
            if (line[i] == '#') {
                ast.push_back(Asteroid(i, p));
                numAst++;
            }
        }
        p++;
    }

    std::vector<double> list;
    int max = 0;
    for (unsigned int i = 0; i < ast.size(); i++) {
        Asteroid current = ast[i];
        double angle;

        int compare;
        for (unsigned int j = 0; j < ast.size(); j++) {
            Asteroid test = ast[j];
            bool present = false;
            if ((test.xCoord != current.xCoord) ||
                (test.yCoord != current.yCoord)) {
                current.SetAngleDistance(test.xCoord, test.yCoord);
                angle = current.getAngle();
            }
            if (list.size() == 0) {
                list.push_back(angle);
            }
            for (unsigned int k = 0; k < list.size(); k++) {
                if (list[k] == angle) {
                    present = true;
                }
            }
            if (!present) {
                list.push_back(angle);
            }
        }
        compare = list.size();

        if (max < compare) {
            xBest = current.xCoord;
            yBest = current.yCoord;
            track[xBest][yBest] = ast;
        }

        max = std::max(max, compare);
        list.clear();
    }

    std::vector<std::pair<double, double>> vect;
    int p2X;
    int p2Y;
    // p2
    {
        Asteroid asteroid(xBest, yBest);
        std::vector<double> angles;
        std::vector<double> dists;
        int num = 0;
        for (unsigned int j = 0; j < ast.size(); j++) {
            Asteroid test = ast[j];
            if ((test.xCoord != asteroid.xCoord) ||
                (test.yCoord != asteroid.yCoord)) {
                asteroid.SetAngleDistance(test.xCoord, test.yCoord);
                dists.push_back(asteroid.getDist());
                angles.push_back(asteroid.getAngle());
                num++;
            }
        }

        for (int i = 0; i < num; i++) {
            vect.push_back(std::make_pair(dists[i], angles[i]));
        }

        for (int i = 0; i < num - 1; i++) {
            for (int j = 0; j < num - i - 1; j++) {
                if (vect[j].second < vect[j + 1].second) {
                    swap(&vect[j], &vect[j + 1]);
                }
            }
        }

        for (int i = 0; i < num - 1; i++) {
            for (int j = 0; j < num - i - 1; j++) {
                if (vect[j].second == vect[j + 1].second) {
                    if (vect[j].first > vect[j + 1].first) {
                        swap(&vect[j], &vect[j + 1]);
                    }
                }
            }
        }
        std::vector<std::pair<double, double>> rip;
        for (unsigned int i = 0; i < vect.size(); i++) {
            rip.push_back(vect[i]);
        }
        vect.clear();

        int find = 0;
        for (unsigned int i = 0; i < rip.size(); i++) {
            if (int(rip[i].second) == 90) {
                find = i;
                break;
            }
        }
        for (unsigned int i = find; i < rip.size(); i++) {
            vect.push_back(rip[i]);
        }
        for (int i = 0; i < find; i++) {
            vect.push_back(rip[i]);
        }

        std::vector<std::pair<double, double>> temp;

        while (temp.size() < 299) {
            unsigned int count = 0;
            while (count < vect.size()) {
                temp.push_back(vect[count]);
                double temp2 = vect[count].second;
                // double temp3 = vect[count].first;
                vect.erase(vect.begin() + count);
                // if (temp2 == vect[count].second) {
                    while (temp2 == vect[count + 1].second) {
                        count++;
                    }

                if (vect[count].second == temp2) {
                    count++;
                }
            }
        }

        double d = temp[199].first;
        double a = temp[199].second * PI / 180;

        p2X = d * std::cos(a);
        p2Y = d * std::sin(a);

        // std::cout << d << std::endl;
        // std::cout << a << std::endl;
        // std::cout << xBest + p2X << std::endl;
        // std::cout << yBest - p2Y<< std::endl;
    }
    int p2 = (xBest + p2X) * 100 + (yBest - p2Y - 1);
    std::cout << max << std::endl;
    std::cout << '(' << max << ',' << p2 << ')' << std::endl;
    return 0;
}