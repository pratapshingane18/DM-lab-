// Include the necessary header for input and output operations and algorithms
#include <bits/stdc++.h>
using namespace std;

// Define a struct to represent the data structure
struct Data {
    string className;
    string category;
    int count;
};

// Main function
int main() {
    // Read input data from a CSV file
    vector<Data> data; // To store the data

    // Open the input file
    ifstream file("expt5_input.csv");

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error in opening input file." << endl;
        return 1;
    }

    string line;

    // Read each line from the file
    while (getline(file, line)) {
        // Skip the header line
        if (line.find("Class,Category,Count") != string::npos) {
            continue;
        }

        // Use stringstream to parse CSV values from the line
        istringstream iss(line);
        string className, category, countStr;

        // Extract className, category, and count from the line
        getline(getline(getline(iss, className, ','), category, ','), countStr, ',');

        // Create a Data entry and add it to the data vector
        Data entry;
        entry.className = className;
        entry.category = category;
        entry.count = stoi(countStr);

        data.push_back(entry);
    }

    // Extract unique classes and categories
    vector<string> classes;
    vector<string> categories;

    // Iterate through the data to find unique classes and categories
    for (const auto& entry : data) {
        if (find(classes.begin(), classes.end(), entry.className) == classes.end()) {
            classes.push_back(entry.className);
        }

        if (find(categories.begin(), categories.end(), entry.category) == categories.end()) {
            categories.push_back(entry.category);
        }
    }

    // Create and initialize count matrix
    vector<vector<int>> counts(classes.size(), vector<int>(categories.size(), 0));

    // Fill the count matrix based on the data
    for (const auto& entry : data) {
        int classIndex = distance(classes.begin(), find(classes.begin(), classes.end(), entry.className));
        int categoryIndex = distance(categories.begin(), find(categories.begin(), categories.end(), entry.category));
        counts[classIndex][categoryIndex] = entry.count;
    }

    // Calculate row sums and column sums
    vector<int> rowSums(classes.size(), 0);
    vector<int> colSums(categories.size(), 0);

    // Calculate the sums of rows and columns in the count matrix
    for (size_t i = 0; i < classes.size(); ++i) {
        for (size_t j = 0; j < categories.size(); ++j) {
            rowSums[i] += counts[i][j];
            colSums[j] += counts[i][j];
        }
    }

    // Calculate T-weights and D-weights
    vector<vector<double>> tWeights(classes.size(), vector<double>(categories.size()));
    vector<vector<double>> dWeights(classes.size(), vector<double>(categories.size()));

    // Calculate T-weights and D-weights based on the row and column sums
    for (size_t i = 0; i < classes.size(); ++i) {
        for (size_t j = 0; j < categories.size(); ++j) {
            tWeights[i][j] = (double)counts[i][j] / rowSums[i] * 100;
            dWeights[i][j] = (double)counts[i][j] / colSums[j] * 100;
        }
    }

    // Print the T-weights and D-weights
    cout << "T-Weights:\n";
    for (size_t i = 0; i < tWeights.size(); ++i) {
        for (size_t j = 0; j < tWeights[i].size(); ++j) {
            cout << classes[i] << ", " << categories[j] << " (T-Weight): " << tWeights[i][j] << "%" << endl;
        }
    }

    cout << "\nD-Weights:\n";
    for (size_t i = 0; i < dWeights.size(); ++i) {
        for (size_t j = 0; j < dWeights[i].size(); ++j) {
            cout << classes[i] << ", " << categories[j] << " (D-Weight): " << dWeights[i][j] << "%" << endl;
        }
    }

    // Close the input file
    file.close();

    return 0;
}
