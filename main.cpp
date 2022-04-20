#include "AdjacencyList.h"
#include "PriorityQueue.h"

void PrintMenuList(AdjacencyList& graph);
void PrintMenuQueue(PriorityQueue& queue);

//Implementation of chrono referenced from Stack Overflow
//https://tinyurl.com/3nbhexre
int main() {
    using namespace chrono;
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

    cout << "Welcome to Cooking Mama's Recipe Book!" << endl;
    cout << endl << "Where would you like to store your recipes?" << endl;
    cout << "0. Exit Menu" << endl;
    cout << "1. Priority Queue" << endl;
    cout << "2. Adjacency List" << endl;
    int option;
    cin >> option;

    if (option != 0) {

        if (option == 1) {
            //initialize the priority queue
            PriorityQueue queue;
            queue.ReadFile();

            auto t1 = high_resolution_clock::now();
            PrintMenuQueue(queue);
            auto t2 = high_resolution_clock::now();

            duration<double, milli> ms_double = t2 - t1;
            cout << endl << ms_double.count() << "ms\n";
        }
        else {
            //initialize the adjacency list
            AdjacencyList graph;
            graph.ReadFile();

            auto t1 = high_resolution_clock::now();
            PrintMenuList(graph);
            auto t2 = high_resolution_clock::now();

            duration<double, milli> ms_double = t2 - t1;
            cout << endl << ms_double.count() << "ms\n";
        }
    }
    cout << "Happy cooking!";
    return 0;
}

void PrintMenuList(AdjacencyList& graph) {
    int option;
    cout << endl << "0. Exit Menu" << endl;
    cout << "1. Input ingredients" << endl;
    cin >> option;
    vector<string> ing;

    if (option == 1) {
        cout << "Note, ingredients should be entered separated by a comma with no spaces." << endl;
        cout << "The minimum amount of ingredients entered should be three." << endl;
        string list;
        cin >> list;

        string res;
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == ',') {
                ing.push_back(res);
                res = "";
            }
            else {
                res += list[i];
            }

            if (i == list.size() - 1) {
                ing.push_back(res);
            }
        }

        cout << endl << "Retrieving matching recipes for you..." << endl;
        option = 2;
    }

    graph.BFS(ing);
    while (option != 0) {
        Recipe r;

        while (option != 1 && option != 0) {
            r = graph.extractMin();

            cout << endl << "Here is your recipe!" << endl;
            cout << "Recipe Name: " << r.name << endl;
            cout << "Minutes: " << r.minutes << endl;
            cout << endl << "What would you like to do?" << endl;

            cout << "0. Exit Menu" << endl;
            cout << "1. Print Recipe Steps and Ingredients" << endl;
            cout << "2. Show Different Recipe" << endl;
            cin >> option;
        }

        if (option == 1) {
            cout << endl << "Here are the ingredients you need:" << endl;
            for (int i = 0; i < r.ingredients.size(); i++) {
                cout << i << ". " << r.ingredients[i] << endl;
            }
            cout << endl << "Here are the steps for your recipe:" << endl;
            for (int i = 0; i < r.steps.size(); i++) {
                cout << i << ". " << r.steps[i] << endl;
            }
        }

        option = 0;
    }
}

void PrintMenuQueue(PriorityQueue& queue) {
    int option;
    cout << endl << "0. Exit Menu" << endl;
    cout << "1. Input ingredients" << endl;
    cin >> option;
    vector<string> ing;

    if (option == 1) {
        cout << "Note, ingredients should be entered separated by a comma with no spaces." << endl;
        cout << "The minimum ingredients entered should be three." << endl;
        string list;
        cin >> list;

        string res;
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == ',') {
                ing.push_back(res);
                res = "";
            }
            else {
                res += list[i];
            }

            if (i == list.size() - 1) {
                ing.push_back(res);
            }
        }

        cout << endl << "Retrieving matching recipes for you..." << endl;
        option = 2;
    }

    queue.selectRecipe(ing);
    while (option != 0) {
        Recipe r;

        while (option != 1 && option != 0) {
            r = queue.extractMin();

            cout << endl << "Here is your recipe!" << endl;
            cout << "Recipe Name: " << r.name << endl;
            cout << "Minutes: " << r.minutes << endl;
            cout << endl << "What would you like to do?" << endl;

            cout << "0. Exit Menu" << endl;
            cout << "1. Print Recipe Steps and Ingredients" << endl;
            cout << "2. Show Different Recipe" << endl;
            cin >> option;
        }

        if (option == 1) {
            cout << endl << "Here are the ingredients you need:" << endl;
            for (int i = 0; i < r.ingredients.size(); i++) {
                cout << i << ". " << r.ingredients[i] << endl;
            }
            cout << endl << "Here are the steps for your recipe:" << endl;
            for (int i = 0; i < r.steps.size(); i++) {
                cout << i << ". " << r.steps[i] << endl;
            }
        }

        option = 0;
    }
}

