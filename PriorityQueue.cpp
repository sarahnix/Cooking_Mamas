#include "PriorityQueue.h"

void PriorityQueue::InitializeQueue(Recipe &r) {
    if (pqSize == 99999) {
        insert(r);
    }
}

//Referenced Sarah Nix's code from Lab 7 COP3503
void PriorityQueue::ReadFile() {
    ifstream inFile("Final_recipes.csv");

    if (inFile.is_open()) {

        string line;
        getline(inFile, line);

        while (getline(inFile, line)) {
            istringstream stream(line);

            string recipeName, id, tempMIN, contr, sub, tags, nut, num, tempSTEPS, tempING, ning;

            int minutes;
            string temp, temp2, temp3, temp4, temp5;

            getline(stream, recipeName, ',');
            getline(stream, id, ',');
            getline(stream, tempMIN, ',');
            getline(stream, contr, ',');
            getline(stream, sub, ',');
            getline(stream, temp, '"');
            getline(stream, tags, '"');
            getline(stream, temp2, ',');
            getline(stream, temp3, '"');
            getline(stream, nut, '"');
            getline(stream, num, '"');
            getline(stream, tempSTEPS, '"');
            getline(stream, temp4, ',');
            getline(stream, temp5, '"');
            getline(stream, tempING, '"');
            getline(stream, ning);

            Recipe recipe;
            recipe.name = recipeName;
            recipe.minutes = stoi(tempMIN);
            recipe.steps = InitializeSteps(tempSTEPS);
            recipe.ingredients = InitializeIngredients(tempING);

            //outlier ingredients contained delimiters within rows and will not be included
            if (!recipe.ingredients.empty()) {
                InitializeQueue(recipe);
            }
        }

    }
}

vector<string> PriorityQueue::InitializeSteps(string &step) {
    vector<string> steps;
    string x;
    bool cont = true;
    bool add = false;

    for (int i = 0; i < step.length(); i++) {
        if (cont) {
            if (step[i] == 39) {
                if (i + 1 < step.length()) {
                    if (step[i+1] != 34 && step[i+1] != 39 && step[i+1] != 44 && step[i+1] != 91 && step[i+1] != 93) {
                        add = true;
                        cont = false;
                    }
                }
            }
        }
        else if (add) {
            x += step[i];
            if (step[i+1] == 39) {
                steps.push_back(x);
                x = "";
                cont = true;
                add = false;
            }
        }
    }

    return steps;
}

vector<string> PriorityQueue::InitializeIngredients(string &ing) {
    vector<string> ingredients;
    string x;
    bool cont = true;
    bool add = false;

    for (int i = 0; i < ing.length(); i++) {
        if (cont) {
            if (ing[i] == 39) {
                if (i + 1 < ing.length()) {
                    if (ing[i+1] != 34 && ing[i+1] != 39 && ing[i+1] != 44 && ing[i+1] != 91 && ing[i+1] != 93) {
                        add = true;
                        cont = false;
                    }
                }
            }
        }
        else if (add) {
            x += ing[i];
            if (ing[i+1] == 39) {
                ingredients.push_back(x);
                x = "";
                cont = true;
                add = false;
            }
        }
    }

    return ingredients;
}


//The following functions were referenced from GeeksforGeeks
//https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
int PriorityQueue::parent(int i) {
    return (i - 1) / 2;
}

int PriorityQueue::leftChild(int i) {
    return ((2 * i) + 1);
}

int PriorityQueue::rightChild(int i) {
    return ((2 * i) + 2);
}

void PriorityQueue::shiftUp(int i) {
    while (i > 0 && R[parent(i)].minutes > R[i].minutes) {

        swap(R[parent(i)], R[i]);

        i = parent(i);
    }
}

void PriorityQueue::shiftDown(int i) {
    int maxIndex = i;

    int l = leftChild(i);

    if (l <= RSize && R[l].minutes < R[maxIndex].minutes) {
        maxIndex = l;
    }

    int r = rightChild(i);

    if (r <= RSize && R[r].minutes < R[maxIndex].minutes) {
        maxIndex = r;
    }

    if (i != maxIndex) {
        swap(R[i], R[maxIndex]);
        shiftDown(maxIndex);
    }
}

void PriorityQueue::insert(Recipe& r) {
    RSize = RSize + 1;
    R[RSize] = r;

    shiftUp(RSize);
}

Recipe PriorityQueue::extractMin() {
    Recipe result = R[0];

    R[0] = R[RSize];
    RSize = RSize - 1;

    shiftDown(0);
    return result;
}

//Function to insert into a priority queue select recipes which contain all the ingredients given by the user
Recipe PriorityQueue::selectRecipe(vector<string> ing) {
    for (int i = 0; i < RSize; i++) {
        Recipe r = extractMin();

        int count = 0;
        if (ing.size() < r.ingredients.size()) {
            for (int j = 0; j < ing.size(); j++) {
                for (int k = 0; k < r.ingredients.size(); k++) {
                    if (ing[j] == r.ingredients[k]) {
                        count++;
                    }
                }
            }
        }
        if (count == ing.size()) {
            return r;
        }
    }

    Recipe recipe;
    cout << "No recipes found" << endl;
    return recipe;
}
