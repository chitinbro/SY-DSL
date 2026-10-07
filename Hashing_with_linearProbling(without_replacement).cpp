#include <iostream>
#include <vector>

using namespace std;

class LinearProbingWithoutReplacement {
private:
    int TABLE_SIZE;
    vector<int> table;
    vector<bool> occupied;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    LinearProbingWithoutReplacement(int size) : TABLE_SIZE(size), table(size, -1), occupied(size, false) {}

    void insert(int key) {
        int hashIndex = hashFunction(key);
        int startIndex = hashIndex;

        for (int i = 0; i < TABLE_SIZE; ++i) {
            int probeIndex = (hashIndex + i) % TABLE_SIZE;
            if (!occupied[probeIndex]) {
                table[probeIndex] = key;
                occupied[probeIndex] = true;
                return;
            }
        }
        cout << "Hash table is full! Cannot insert " << key << endl;
    }

    void display() {
        cout << "\n--- Hash Table (Without Replacement) ---\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Index " << i << ": ";
            if (occupied[i]) cout << table[i];
            else cout << "EMPTY";
            cout << endl;
        }
    }
};
