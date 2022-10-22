#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream> 
#include <map>
#include <algorithm>
#include <ctime>
#include <set>
#include "Evolution.hpp"
#include "Prepare.hpp"

double X[1000], Y[1000];
double dimensions[1000][1000];
int N;          // number of cities
int pop_size;
//std::string fileName = "berlin11_modified.tsp";
std::string fileName = "berlin52.tsp";

int loader(std::string filename) {
    int line = 0;
    int i = 1;
    std::string path = "C:/Users/PLUSR6000280/Documents/Studia/AlgorytmyInspirowaneNatura/Zadanie0/";
    std::ifstream file(path + filename);
    std::string temp;

    while (std::getline(file, temp)) {
        if (temp == "EOF") {
            break;
        }
        if (line == 3) {
            std::vector<std::string> stringVector = split(temp, ' ');
            N = std::stoi(stringVector[1]);
        }
        if (line > 5) {
            std::vector<std::string> stringVector = split(temp, ' ');
            X[i] = std::stod(stringVector[1]);
            //std::cout << X[i] << " ";
            Y[i] = std::stod(stringVector[2]);
            //std::cout << Y[i] << std::endl;

            i++;
        }
        line++;
    }

    file.close();

    std::cout << "Read " << N << " variables" << std::endl;
    return N;
}

int main() {
    srand(time(NULL));
    int N;
    double randomResultSum = 0, randomMinResult = DBL_MAX, randomMaxResult = 0;
    double greedyResultSum = 0, greedyMinResult = DBL_MAX, greedyMaxResult = 0;
    double geneticResultSum = 0, geneticMinResult = DBL_MAX, geneticMaxResult = 0;

    // For now hardcoded, can be changed later
    N = loader(fileName);
    createDistanceMatrix(N, false);

// Random 10k records
//

/*
   for (int i = 0; i < 10000;i++) {
        std::vector<int> randomResult = random(N);
        double calculatedResult = calculateResultDst(randomResult);
        randomResultSum += calculatedResult;
        randomMinResult = std::min(randomMinResult, calculatedResult);
        randomMaxResult = std::max(randomMaxResult, calculatedResult);
    }

    std::cout << "Random result x10k: " << randomResultSum / 10000 << std::endl;
    std::cout << "Random min result: " << randomMinResult << std::endl;
    std::cout << "Random max result: " << randomMaxResult << std::endl;
    
*/

// Greedy 10 records
// zawsze wybiera najblizsze miasto
/*
    for (int i = 1; i <= N; i++) {
        std::vector<int> greedyPath = greedy(N, i);
        double calculatedGreedyResult = calculateResultDst(greedyPath);
        greedyResultSum += calculatedGreedyResult;
        greedyMinResult = std::min(greedyMinResult, calculatedGreedyResult);
        greedyMaxResult = std::max(greedyMaxResult, calculatedGreedyResult);
    }

    std::cout << "Greedy result for each city: " << greedyResultSum / N << std::endl;
    std::cout << "Greedy min result: " << greedyMinResult << std::endl;
    std::cout << "Greedy max result: " << greedyMaxResult << std::endl;
*/

// Genetic algorithm
//
    for (int i = 1; i <= 10; i++) {
        std::cout << "iteration" << i << std::endl;
        std::vector<int> geneticPath = evolution(N);
        double calculatedGeneticResult = calculateResultDst(geneticPath);
        geneticResultSum += calculatedGeneticResult;
        geneticMinResult = std::min(geneticMinResult, calculatedGeneticResult);
        geneticMaxResult = std::max(geneticMaxResult, calculatedGeneticResult);
    }

    std::cout << "Genetic result for each city: " << geneticResultSum / 10 << std::endl;
    std::cout << "Genetic min result: " << geneticMinResult << std::endl;
    std::cout << "Genetic max result: " << geneticMaxResult << std::endl;

    std::cout;
    std::cout;
}
