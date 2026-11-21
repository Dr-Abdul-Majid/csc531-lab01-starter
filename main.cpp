#include <iostream>
#include "lab01.hpp"

int main() {
    constexpr int CAP = 8;
    int values[CAP] = {70, 80, 90, 85};
    int size = 4;

    int choice = 0;
    while (choice != 4) {
        std::cout << "\n1. Display active values and logical size\n";
        std::cout << "2. Insert\n";
        std::cout << "3. Delete\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "Active values (size = " << size << "): ";
            for (int i = 0; i < size; ++i) std::cout << values[i] << ' ';
            std::cout << '\n';
        } else if (choice == 2) {
            int pos, x;
            std::cout << "Enter position and value: ";
            std::cin >> pos >> x;
            if (insertAt(values, size, CAP, pos, x)) {
                std::cout << "Inserted.\n";
            } else {
                std::cout << "Insert failed.\n";
            }
        } else if (choice == 3) {
            int pos;
            std::cout << "Enter position: ";
            std::cin >> pos;
            if (deleteAt(values, size, pos)) {
                std::cout << "Deleted.\n";
            } else {
                std::cout << "Delete failed.\n";
            }
        } else if (choice == 4) {
            std::cout << "Exiting.\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
