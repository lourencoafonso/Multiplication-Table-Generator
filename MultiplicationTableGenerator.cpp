#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <iomanip>
#include <sstream>

using namespace std;

tuple<float, int> getMultiplicationTableSize() {
    float numberToMultiply;
    int tableSize;

    while (true) {
        // Get number to multiply
        try {
            string temp;
            cout << "Enter the number you want to multiply: ";
            cin >> temp;
            numberToMultiply = stof(temp);

            if (numberToMultiply == 0) {
                cout << "Please enter a number not equal to 0.\n";
                continue;
            }
        } catch (invalid_argument&) {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        // Get table size
        while (true) {
            try {
                string temp;
                cout << "Enter the size of the multiplication table: ";
                cin >> temp;
                tableSize = stoi(temp);

                if (tableSize <= 0) {
                    cout << "Please enter a positive integer.\n";
                    continue;
                }
            } catch (invalid_argument&) {
                cout << "Invalid input. Please enter a valid integer.\n";
                continue;
            }

            return {numberToMultiply, tableSize};
        }
    }
}

string formatNumber(float num) {
    stringstream ss;
    ss << fixed << setprecision(2) << num;  // cap to 2 decimals
    return ss.str();
}

int main () {
    cout << "Welcome to the Multiplication Table Generator!" << endl;

    while (true) {
        auto [numberToMultiply, tableSize] = getMultiplicationTableSize();

        // Format number to two decimals for filename
        string formattedNum = formatNumber(numberToMultiply);

        string fileName = "MultiplicationTable_" + formattedNum + ".csv";
        ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            outputFile << "Multiplication Table for " << numberToMultiply << "\n";

            for (int i = 1; i <= tableSize; ++i) {
                outputFile << numberToMultiply << " * " << i
                           << " = " << numberToMultiply * i << "\n";
            }

            outputFile.close();
            cout << "Saved to: " << fileName << "\n\n";
        } else {
            cout << "Error: Could not open file for writing." << endl;
        }

        // Ask user if they want another table
        cout << "Generate another multiplication table? (y/n): ";
        char choice;
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;
}
