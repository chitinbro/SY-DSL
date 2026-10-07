#include <iostream>
#include <vector>

using namespace std;

class LinearProbingWithReplacement {
private:
    int TABLE_SIZE;
    vector<int> table;
    vector<bool> occupied;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    LinearProbingWithReplacement(int size) : TABLE_SIZE(size), table(size, -1), occupied(size, false) {}

    void insert(int key) {
        int homeIndex = hashFunction(key);
        int currIndex = homeIndex;

        // Find the first empty slot using linear probing
        int insertPos = -1;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            int idx = (homeIndex + i) % TABLE_SIZE;
            if (!occupied[idx]) {
                insertPos = idx;
                break;
            }
        }

        if (insertPos == -1) {
            cout << "Hash table is full! Cannot insert " << key << endl;
            return;
        }

        // Check if we need replacement: look at the element currently at hashFunction(key)
        // If the element at homeIndex has a different home index than homeIndex itself,
        // we displace it to make room for the key that naturally belongs at homeIndex.
        int tempKey = key;
        int targetPos = homeIndex;

        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (!occupied[targetPos]) {
                table[targetPos] = tempKey;
                occupied[targetPos] = true;
                break;
            }

            // Check if the current occupant's home address is its current position
            int occupantHome = hashFunction(table[targetPos]);
            if (occupantHome != targetPos && occupantHome == hashFunction(tempKey)) {
                // Displace the resident
                int displaced = table[targetPos];
                table[targetPos] = tempKey;
                tempKey = displaced;
            }

            targetPos = (targetPos + 1) % TABLE_SIZE;
        }
    }

    void display() {
        cout << "\n--- Hash Table (With Replacement) ---\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Index " << i << ": ";
            if (occupied[i]) cout << table[i] << " (Home: " << hashFunction(table[i]) << ")";
            else cout << "EMPTY";
            cout << endl;
        }
    }
};

int main() {
    cout << "Testing Without Replacement:\n";
    LinearProbingWithoutReplacement ht1(7);
    ht1.insert(10);
    ht1.insert(17); // Collides with 10 (17 % 7 == 3, 10 % 7 == 3)
    ht1.insert(3);  // Collides at index 3
    ht1.display();

    cout << "\nTesting With Replacement:\n";
    LinearProbingWithReplacement ht2(7);
    ht2.insert(10);
    ht2.insert(17);
    ht2.insert(3);
    ht2.display();

    return 0;
}
