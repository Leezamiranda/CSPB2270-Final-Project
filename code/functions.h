#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>
#include <ctime>

using namespace std;


class Task {
public:
    string taskName;
    time_t startTime;
    int recurrenceInterval;

    Task(const string& name, time_t startTime, int recurrenceInterval);
    
    void reschedule();

    void display() const;
};

class Node {
public:
    time_t key;
    Task* data;
    vector<Node*> forward;

    Node(time_t key, Task* data, int level);
};

class SkipList {
private:
    int maxLevel;
    float probability;
    Node* head;
    int currentLevel;

    int generateLevel();

    Node* init_Node(time_t key, Task* data, int level);

public:
    Node* get_head() const{
        return head;
    }

    SkipList(int maxLevel, float probability);

    ~SkipList();

    void insert(Task* data);

    Task* search(time_t key);

    void erase(time_t key);

    void rescheduleTask(Node* node);
};

#endif // FUNCTIONS_H
