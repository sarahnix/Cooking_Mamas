#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#pragma once
using namespace std;

class Recipe {

public:
    string name;
    int minutes;
    vector<string> steps;
    vector<string> ingredients;

    Recipe();
};
