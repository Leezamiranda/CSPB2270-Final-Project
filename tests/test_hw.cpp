#include "../code/functions.h"
#include <iostream>
using namespace std;

void testInsert(SkipList& list) {
    cout << "Testing Insert...\n";

    list.insert(3, "Three");
    list.insert(7, "Seven");
    list.insert(9, "Nine");
    list.insert(12, "Twelve");

    cout << "Expected: Three, Found: " << list.search(3) << endl;
    cout << "Expected: Seven, Found: " << list.search(7) << endl;
    cout << "Expected: Nine, Found: " << list.search(9) << endl;
    cout << "Expected: Twelve, Found: " << list.search(12) << endl;
}

void testSearch(SkipList& list) {
    cout << "Testing Search...\n";

    // Test for existing keys
    cout << "Search 3: " << (list.search(3) == "Three" ? "Pass" : "Fail") << endl;
    cout << "Search 9: " << (list.search(9) == "Nine" ? "Pass" : "Fail") << endl;

    // Test for non-existing keys
    cout << "Search 100: " << list.search(100) << " (Expected: Entry does not exist)" << endl;
}

void testErase(SkipList& list) {
    cout << "Testing Erase...\n";

    list.erase(3); // Erase existing key
    cout << "Erase 3: " << list.search(3) << " (Expected: Entry does not exist)" << endl;

    list.erase(100); // Erase non-existing key
    cout << "Erase 100: (No error expected)\n";
}

void testEdgeCases(SkipList& list) {
    cout << "Testing Edge Cases...\n";

    // Insert duplicate key
    list.insert(7, "Seven Updated");
    cout << "Update key 7: " << list.search(7) << " (Expected: Seven Updated)" << endl;

    // Insert a large range of numbers
    for (int i = 1; i <= 10; i++) {
        list.insert(i * 10, "Value" + to_string(i * 10));
    }

    cout << "Search 10: " << list.search(10) << " (Expected: Value10)" << endl;
    cout << "Search 100: " << list.search(100) << " (Expected: Value100)" << endl;
}

int main() {
    // Create a Skip List
    SkipList list(5, 0.5); // Max level = 5, Probability = 0.5

    // Run tests
    testInsert(list);
    testSearch(list);
    testErase(list);
    testEdgeCases(list);

    return 0;
}
