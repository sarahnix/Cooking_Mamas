#include "AdjacencyList.h"

void AdjacencyList::InitializeGraph(Recipe &r) {
    for (int i = 0; i < cookbook.size(); i++) {
        float temp = ReturnIndex(r, cookbook[i]);
        if (temp != 0.00) {
            InsertEdge(r.name, cookbook[i].name, temp);
        }
    }
}

void AdjacencyList::InsertEdge(string from, string to, float weight) {
    recipes[from].push_back(make_pair(to, weight));
    recipes[to].push_back(make_pair(from, weight));
}

float AdjacencyList::ReturnIndex(Recipe& r1, Recipe& r2) {
    float weight;
    int count = 0;

    if (r1.ingredients.size() < r2.ingredients.size()) {

        for (int i = 0; i < r1.ingredients.size(); i++) {
            for (int j = 0; j < r2.ingredients.size(); j++) {
                if (r1.ingredients[i] == r2.ingredients[j]) {
                    count++;
                }
            }
        }
        if (count != 0) {
            weight = (float) count / (r1.ingredients.size());
        }
        else {
            weight = 0.00;
        }
    }
    else {

        for (int i = 0; i < r2.ingredients.size(); i++) {
            for (int j = 0; j < r1.ingredients.size(); j++) {
                if (r2.ingredients[i] == r1.ingredients[j]) {
                    count++;
                }
            }
        }
        if (count != 0) {
            weight = (float) count / (r2.ingredients.size());
        }
        else {
            weight = 0.00;
        }
    }

    return weight;
}

//Referenced Sarah Nix's code from Lab 7 COP3503
void AdjacencyList::ReadFile() {
    ifstream inFile("temp_recipes4.csv");

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
                InitializeGraph(recipe);
                cookbook.push_back(recipe);
                recipeList[recipe.name] = recipe;
            }
        }

    }
}

vector<string> AdjacencyList::InitializeSteps(string& step) {
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

vector<string> AdjacencyList::InitializeIngredients(string& ing) {
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

//Referenced Sarah Nix's stepik code (which was inspired from Aman's slides)
void AdjacencyList::BFS(vector<string>& ing) {
    auto src = recipes.begin();
    unordered_map<string, bool> beenThere;
    beenThere[src->first] = true;

    queue<string> q;
    q.push(src->first);

    while (!q.empty()) {
        string i = q.front();

        int count = 0;
        for (int k = 0; k < ing.size(); k++) {
            for (int m = 0; m < recipeList[i].ingredients.size(); m++) {
                if (ing[k] == recipeList[i].ingredients[m]) {
                    count++;
                }
            }

        }
        if (count == ing.size()) {
            if (size < 499) {
                insertToPQ(recipeList[i].name);
            }
            else {
                return;
            }
        }

        q.pop();

        for (int j = 0; j < recipes[i].size(); j++) {
            if (!beenThere[recipes[i][j].first]) {
                beenThere[recipes[i][j].first] = true;
                q.push(recipes[i][j].first);
            }
        }
    }
}


//The following functions were referenced from GeeksforGeeks
//https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
int AdjacencyList::parent(int i) {
    return (i - 1) / 2;
}

int AdjacencyList::leftChild(int i) {
    return ((2 * i) + 1);
}

int AdjacencyList::rightChild(int i) {
    return ((2 * i) + 2);
}

void AdjacencyList::heapifyUp(int i) {
    while(i > 0 && recipeList[pq[parent(i)]].minutes > recipeList[pq[i]].minutes){
        swap(pq[parent(i)], pq[i]);

        i = parent(i);
    }
}

void AdjacencyList::heapifyDown(int i) {
    int minIndex = i;

    int left = leftChild(i);

    if(left <= size && recipeList[pq[left]].minutes < recipeList[pq[minIndex]].minutes){
        minIndex = left;
    }

    int right = rightChild(i);

    if(right <= size && recipeList[pq[right]].minutes < recipeList[pq[minIndex]].minutes){
        minIndex = right;
    }

    if(i != minIndex){
        swap(pq[i], pq[minIndex]);
        heapifyDown(minIndex);
    }

}

void AdjacencyList::insertToPQ(string r) {
    size = size + 1;
    pq[size] = r;

    heapifyUp(size);
}

Recipe AdjacencyList::extractMin() {
    Recipe resultRecipe = recipeList[pq[0]];

    pq[0] = pq[size];
    size = size - 1;

    heapifyDown(0);
    return resultRecipe;
}
