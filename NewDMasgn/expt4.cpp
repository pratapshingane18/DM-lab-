// Include necessary header for input and output operations
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Open the input file
    ifstream inputFile("expt4_input.csv");

    // Declare variables to store CSV column values
    string line, day, level, study, routine, value;

    // Maps to store counts of parent and child occurrences
    map<string, int> parentCounts;
    map<string, map<string, int>> childCounts;

    // Check if the input file is open
    if (!inputFile.is_open()) {
        cerr << "Error in opening the input file." << endl;
        return -1;
    }

    // Variables to store the user's choice of column and line index
    int columnChoice;
    int lineIndex = 0;
    string childName;

    // Read each line from the input file
    while (getline(inputFile, line)) {
        // Use stringstream to parse CSV values from the line
        stringstream lineStream(line);
        getline(lineStream, day, ',');
        getline(lineStream, level, ',');
        getline(lineStream, study, ',');
        getline(lineStream, routine, ',');
        getline(lineStream, value, ',');

        // Skip the header line
        if (lineIndex == 0) {
            lineIndex++;
            // Prompt the user to enter the column number for the child attribute
            cout << "Enter Child Column Number: ";
            cin >> columnChoice;
            continue;
        }

        // Determine the child attribute based on user choice
        switch (columnChoice) {
            case 1:
                childName = day;
                break;
            case 2:
                childName = level;
                break;
            case 3:
                childName = study;
                break;
            case 4:
                childName = routine;
                break;
            default:
                childName = study;
                break;
        }

        // Update counts in parent and child maps
        parentCounts[routine]++;
        childCounts[childName][routine]++;
    }

    // Calculate the parent entropy
    double positiveCount = parentCounts["Yes"];
    double negativeCount = parentCounts["No"];
    double totalSamples = positiveCount + negativeCount;

    double parentEntropy = -((positiveCount / totalSamples) * log2(positiveCount / totalSamples) +
                             (negativeCount / totalSamples) * log2(negativeCount / totalSamples));

    // Display the parent entropy
    cout << "Parent Entropy: " << parentEntropy << endl;

    // Calculate the child entropy
    double childEntropy = 0;
    for (auto child : childCounts) {
        string childName = child.first;
        double childPositiveCount = childCounts[childName]["Yes"];
        double childNegativeCount = childCounts[childName]["No"];
        double totalChildSamples = childPositiveCount + childNegativeCount;

        childEntropy += -((totalChildSamples / totalSamples) * ((childPositiveCount / totalChildSamples) * log2(childPositiveCount / totalChildSamples) +
            (childNegativeCount / totalChildSamples) * log2(childNegativeCount / totalChildSamples)));
    }

    // Display the information gain
    cout << "Information Gain: " << parentEntropy - childEntropy << endl;

    // Close the input file
    inputFile.close();

    return 0;
}
