#include "Recipe.h"

class AdjacencyList {
private:
    unordered_map<string, vector<pair<string, float>>> recipes;
    unordered_map<string, Recipe> recipeList;
    vector<Recipe> cookbook;

    //Selected Priority Queue for recipes containing the user's ingredients
    string pq[500]; ///this should be changed for testing purposes
    int size = -1;

public:

    void InitializeGraph(Recipe& r);
    void InsertEdge(string from, string to, float weight);
    float ReturnIndex(Recipe& r1, Recipe& r2);

    void ReadFile();
    vector<string> InitializeSteps(string& step);
    vector<string> InitializeIngredients(string& ing);

    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void heapifyUp(int i);
    void heapifyDown(int i);
    void insertToPQ(string r);
    Recipe extractMin();

    void BFS(vector<string>& ing);
};