#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::string> split(std::string, char);
double calculateResultDst(std::vector<int>);
void createDistanceMatrix(int, bool);
std::vector<int> random(int);
std::vector<int> greedy(int, int);