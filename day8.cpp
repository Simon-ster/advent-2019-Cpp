#include "common.hpp"
int findSmallest(int arr[], int n) {
    int temp = arr[0];
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (temp > arr[i]) {
            temp = arr[i];
            index = i;
        }
    }
    return index;
}

int main() {
    freopen("image.txt", "r", stdin);

    int cube[100][6][25] = {2};  //start transparent
    int img[6][25] = {2};

    int layers[100] = {0};
    int c;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 25; k++) {
                c = getchar();
                c -= 48;
                cube[i][j][k] = c;
                if (cube[i][j][k] == 0) {
                    layers[i]++;
                }
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        std::cout << layers[i] << std::endl;
    }

    int index = findSmallest(layers, 100);
    int oneCount = 0;
    int twoCount = 0;
    std::cout << index << std::endl;
    for (int l = 0; l < 25; l++) {
        for (int m = 0; m < 6; m++) {
            if (cube[index][m][l] == 1) {
                oneCount++;
            } else if (cube[index][m][l] == 2) {
                twoCount++;
            } else {
            }
        }
    }
    for (int i = 99; i >= 0; i--) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 25; k++) {
                if (cube[i][j][k] != 2) {
                    img[j][k] = cube[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 25; j++) {
            if (img[i][j] == 1) {
                std::cout << '0';
            } else if (img[i][j] == 0) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    // std::cout << (oneCount * twoCount) << std::endl;
    return 0;
}
