#include "functions.h"
#include <cstdlib>
#include <cmath>

Node::Node(int key, string data, int level) {
    this->key = key;
    this->data = data;
    this->forward = vector<Node*>(level + 1, nullptr);
}

SkipList::SkipList(int maxLevel, float probability) {
    this->maxLevel = maxLevel;
    this->probability = probability;
    this->currentLevel = 0;
    this->head = new Node(-1, "", maxLevel);
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

Node* SkipList::init_Node(int key, string data, int level) {
    return new Node(key, data, level);
}

void SkipList::insert(int key, string data) {
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

string SkipList::search(int key){
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
        return "Entry does not exist";
    }
}

void SkipList::erase(int key){
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

