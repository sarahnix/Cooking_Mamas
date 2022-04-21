#include "Recipe.h"

class PriorityQueue {
private:
    Recipe R[100000]; /// this should be changed for testing purposes (making the video)
    int RSize = -1;

    Recipe pq[500]; ///this can also be changed for testing
    int pqSize = -1;

public:

    void InitializeQueue(Recipe& r);

    void ReadFile();
    vector<string> InitializeSteps(string& step);
    vector<string> InitializeIngredients(string& ing);

    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void shiftUp(int i);
    void shiftDown(int i);
    void insert(Recipe& r);
    Recipe extractMin();

    void subshiftUp(int i);
    void subshiftDown(int i);
    void subinsert(Recipe& r);
    Recipe subextractMin();

    void selectRecipe(vector<string> ing);
    void updatePQ(Recipe& recipe);
};
