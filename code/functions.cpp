#include "functions.h"
#include <cstdlib>
#include <cmath>

Node::Node(time_t key, Task* data, int level) {
    this->key = key;
    this->data = data;
    this->forward = vector<Node*>(level + 1, nullptr);
}

Task::Task(const string& name, time_t startTime, int recurrenceInterval) {
    this->taskName = name;
    this->startTime = startTime;
    this->recurrenceInterval = recurrenceInterval;
}

void Task::reschedule(){
    startTime += recurrenceInterval *60 *60 *24;
}

void Task::display() const {    
    cout << "Task: " << taskName << 
    ", Recurring every: " << recurrenceInterval << " days" << endl;   
}

SkipList::SkipList(int maxLevel, float probability) {
    this->maxLevel = maxLevel;
    this->probability = probability;
    this->currentLevel = 0;
    this->head = new Node(-1, nullptr, maxLevel);
}

SkipList::~SkipList() {
    Node* cursor = head;
    while(cursor != nullptr) {
        Node* doomed = cursor;
        cursor = cursor->forward[0];
        delete doomed;
    }
}

int SkipList::generateLevel() {
    int level = 0;
    while(level < maxLevel && static_cast<float>(rand()) / RAND_MAX < probability) {
        level ++;
    }
    return level;
}

Node* SkipList::init_Node(time_t key, Task* data, int level) {
    return new Node(key, data, level);
}

void SkipList::insert(Task* data) {
    time_t key = data->startTime;
    vector<Node*> update(maxLevel + 1, nullptr);
    Node* cursor = head;

    for(int i = currentLevel; i >= 0; i--){
        while(cursor->forward[i] != nullptr && cursor->forward[i]->key < key){
            cursor = cursor->forward[i];
        }
        update[i] = cursor;
    }

    cursor = cursor->forward[0];
    if(cursor != nullptr && cursor->key == key){
        cursor->data = data;
    }
    else{
        int newLevel = generateLevel();
        if(newLevel > currentLevel){
            for(int i = currentLevel + 1; i <= newLevel; i++){
                update[i] = head;
            }
            currentLevel = newLevel;
        }

        Node* newNode = init_Node(key, data, newLevel);
        for(int i =0; i <= newLevel; i++){
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

Task* SkipList::search(time_t key){
    Node* cursor = head;
    for(int i = currentLevel; i >= 0; i--){
        while(cursor->forward[i] != nullptr && cursor->forward[i]->key < key){
            cursor = cursor->forward[i];
        }
    }
    cursor = cursor->forward[0];
    if(cursor != nullptr && cursor->key == key){
        return cursor->data;
    }
    else{
        return nullptr;
    }
}

void SkipList::erase(time_t key){
    vector<Node*> update(maxLevel + 1, nullptr);
    Node* cursor  = head;

    for(int i = currentLevel; i >=0; i--) {
        while(cursor->forward[i] != nullptr && cursor->forward[i]->key < key) {
            cursor = cursor->forward[i];
        }
        update[i] = cursor;
    }
    cursor = cursor->forward[0];
    if (cursor != nullptr && cursor->key == key) {
        for(int i = 0; i <= currentLevel; i++){
            if (update[i]->forward[i] != cursor) break;
            update[i]->forward[i]= cursor->forward[i];
        }
        delete cursor;
        while(currentLevel > 0 && head->forward[currentLevel] == nullptr){
            currentLevel --;
        }
    }
}

void SkipList::rescheduleTask(Node* node) {
    Task* task = node->data;
    time_t newKey = node->key + (node->data->recurrenceInterval * 60 *60 * 24);
    while(search(newKey) != nullptr) {
        newKey += 1;
    }
    erase(node->key);
    task->startTime = newKey;
    insert(task);
}
