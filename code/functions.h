#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
    int key;
    string data;
    vector<Node*> forward;

    Node(int key, string data, int level);
};

class SkipList {
private:
    int maxLevel;
    float probability;
    Node* head;
    int currentLevel;

    int generateLevel();

    Node* init_Node(int key, string data, int level);

public:
    SkipList(int maxLevel, float probability);

    ~SkipList();

    void insert(int key, string data);

    string search(int key);

    void erase(int key);
};

#endif // FUNCTIONS_H
