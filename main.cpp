#include <iostream>
#include "lab01.hpp"

using namespace std;

int main() {
    const int cap = 8;
    int values[] = {70, 80, 90, 85};
    int size = 4;

    int choice;
    while (true) {
        cout << "\n--- Array Menu ---\n";
        cout << "Active values: ";
        if (size == 0) {
            cout << "(empty)";
        } else {
            for (int i = 0; i < size; i++) {
                cout << values[i];
                if (i < size - 1) cout << ", ";
            }
        }
        cout << " | logical size = " << size << endl;
        cout << "1. Display active values\n";
        cout << "2. Insert (ask for position, report success/failure)\n";
        cout << "3. Delete (ask for position, report success/failure)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        if (choice == 1) {
            cout << "Active values: ";
            for (int i = 0; i < size; i++) {
                cout << values[i] << " ";
            }
            cout << "\nLogical size = " << size << endl;
        }
        else if (choice == 2) {
            int pos, value;
            cout << "Enter position (0 to " << size << "): ";
            cin >> pos;
            cout << "Enter value: ";
            cin >> value;
            if (insert(values, size, cap, pos, value)) {
                cout << "Inserted successfully.\n";
            } else {
                cout << "Insertion failed. Invalid position or array is full.\n";
            }
        }
        else if (choice == 3) {
            int pos;
            cout << "Enter position (0 to " << size - 1 << "): ";
            cin >> pos;
            if (deleteElement(values, size, pos)) {
                cout << "Deleted successfully.\n";
            } else {
                cout << "Deletion failed. Invalid position.\n";
            }
        }
        else if (choice == 4) {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
