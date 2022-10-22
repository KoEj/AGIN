#include "Prepare.hpp"

extern double dimensions[1000][1000];
extern double X[1000], Y[1000];

std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream. 
    std::string tok;

    while (std::getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

double calculateResultDst(std::vector<int> vector) {
    double result = 0;
    double dist;
    int startCity = vector.front();

    for (int i = 1; i < vector.size(); i++) {
        dist = dimensions[vector.at(i)][vector.at(i - 1)];
        result += dist;
    }
    result += dimensions[vector.at(vector.size() - 1)][startCity];

    return result;
}

void createDistanceMatrix(int N, bool printMatrix) {
    // start from index number 1
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            double distance = 0;
            if (i != j) {
                distance = std::sqrt(std::pow(X[i] - X[j], 2) + std::pow(Y[i] - Y[j], 2));
            }
            dimensions[i][j] = distance;
        }
    }

    if (printMatrix) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                std::cout << dimensions[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
}

std::vector<int> random(int N) {
    std::vector<int> randomPath;
    int arr[1000];
    bool duplicate = false;
    int i = 0;

    while (i < N) {
        int randomVal = std::rand() % N + 1;
        duplicate = false;

        for (int j = 0; j < i; j++) {
            if (randomVal == arr[j]) {
                duplicate = true;
            }
        }

        if (!duplicate) {
            arr[i] = randomVal;
            i++;
        }
    }

    for (int i = 1; i < N;i++) {
        randomPath.push_back(arr[i - 1]);

        if (i == N - 1) {
            randomPath.push_back(arr[i]);
        }
    }

    return randomPath;
}

std::vector<int> greedy(int N, int startCity) {
    int currentCity = startCity;
    int id = startCity;
    double distance = DBL_MAX;
    double result = 0;
    std::vector<int> path;

    path.push_back(currentCity);

    for (int j = 1; j <= N; j++) {
        for (int i = 1; i <= N; i++) {
            if (dimensions[currentCity][i] != 0 && dimensions[currentCity][i] < distance) {
                if (std::find(path.begin(), path.end(), i) == path.end()) {
                    distance = dimensions[currentCity][i];
                    id = i;
                }
            }
        }

        if (id != 0) {
            path.push_back(id);
        }

        currentCity = id;
        id = 0;
        distance = DBL_MAX;
    }

    return path;
}