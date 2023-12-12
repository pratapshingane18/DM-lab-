//5. Find t and d weight of a data.
#include <bits/stdc++.h>// Include the algorithm header

using namespace std;

struct Data {
    string className;
    string category;
    int count;
};

int main() {
    // Read input data from a CSV file
    vector<Data> data; // To store the data

    ifstream file("expt5_input.csv");

    if (!file.is_open()) {
        cerr << "Error in opening input file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Class,Category,Count") != string::npos) {
            continue; // Skip the header line
        }

        istringstream iss(line);
        string className, category, countStr;

        getline(getline(getline(iss, className, ','), category, ','), countStr, ',');

        Data entry;
        entry.className = className;
        entry.category = category;
        entry.count = stoi(countStr);

        data.push_back(entry);
    }

    // Extract unique classes and categories
    vector<string> classes;
    vector<string> categories;

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

    for (size_t i = 0; i < classes.size(); ++i) {
        for (size_t j = 0; j < categories.size(); ++j) {
            rowSums[i] += counts[i][j];
            colSums[j] += counts[i][j];
        }
    }

    // Calculate T-weights and D-weights
    vector<vector<double>> tWeights(classes.size(), vector<double>(categories.size()));
    vector<vector<double>> dWeights(classes.size(), vector<double>(categories.size()));

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

    return 0;
}