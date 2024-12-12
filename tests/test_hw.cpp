#include "../code/functions.h"
#include <iostream>
#include <ctime>

using namespace std;

void displaySkipList(SkipList& list) {
    Node* cursor = list.get_head()->forward[0]; 
    while (cursor != nullptr) {
        cout << "Key: " << cursor->key << ", ";
        cursor->data->display(); 
        cursor = cursor->forward[0];
    }
    cout << endl;
}


void testInsert(SkipList& list) {
    cout << "Test: Inserting Tasks\n";

    time_t now = time(nullptr);
    Task* task1 = new Task("Daily Report", now + 24 * 60 * 60, 1); 
    Task* task2 = new Task("Weekly Meeting", now + 7 * 24 * 60 * 60, 7); 
    Task* task3 = new Task("Monthly Review", now + 30 * 24 * 60 * 60, 30); 

    list.insert(task1);
    list.insert(task2);
    list.insert(task3);

    Node* cursor = list.get_head()->forward[0];
    bool pass = true;

    
    if (cursor->data->taskName != "Daily Report") pass = false;
    cursor = cursor->forward[0];
    if (cursor->data->taskName != "Weekly Meeting") pass = false;
    cursor = cursor->forward[0];
    if (cursor->data->taskName != "Monthly Review") pass = false;

    cout << (pass ? "PASS" : "FAIL") << ": Tasks inserted correctly.\n";
}


void testSearch(SkipList& list) {
    cout << "Test: Searching for Tasks\n";

    time_t now = time(nullptr);
    Task* foundTask = list.search(now + 24 * 60 * 60); 
    if (foundTask != nullptr && foundTask->taskName == "Daily Report") {
        cout << "PASS: Found Task: ";
        foundTask->display();
    } else {
        cout << "FAIL: Task not found or incorrect task returned.\n";
    }
}


void testDelete(SkipList& list) {
    cout << "Test: Deleting Tasks\n";

    time_t now = time(nullptr);
    list.erase(now + 24 * 60 * 60); 

    Task* foundTask = list.search(now + 24 * 60 * 60);
    if (foundTask == nullptr) {
        cout << "PASS: Task successfully deleted.\n";
    } else {
        cout << "FAIL: Task still exists after deletion.\n";
    }

    cout << "Current Skip List:\n";
    displaySkipList(list);
}


void testReschedule(SkipList& list) {
    cout << "Test: Rescheduling Tasks\n";

    Node* node = list.get_head()->forward[0]; 
    if (node != nullptr) {
        cout << "Rescheduling Task: ";
        node->data->display();

        time_t oldKey = node->key;
        list.rescheduleTask(node);

        
        Task* rescheduledTask = list.search(oldKey + node->data->recurrenceInterval * 60 * 60 * 24);
        if (rescheduledTask != nullptr && rescheduledTask->taskName == node->data->taskName) {
            cout << "PASS: Task rescheduled correctly.\n";
        } else {
            cout << "FAIL: Task not rescheduled correctly.\n";
        }
    } else {
        cout << "FAIL: No task to reschedule.\n";
    }

    cout << "Current Skip List:\n";
    displaySkipList(list);
}

int main() {
    SkipList list(5, 0.5); 

    testInsert(list);
    testSearch(list);
    testDelete(list);
    testReschedule(list);

    return 0;
}
