//2. Perform Normalization of data (Min-max and Z-score).
#include <bits/stdc++.h>
using namespace std;

int findMaxValue(const vector<double>& values) {
    double max = numeric_limits<double>::min();
    for (const double& value : values) {
        if (value > max) {
            max = value;
        }
    }
    return static_cast<int>(max);
}

int findMinValue(const vector<double>& values) {
    double min = numeric_limits<double>::max();
    for (const double& value : values) {
        if (value < min) {
            min = value;
        }
    }
    return static_cast<int>(min);
}

double calculateAverage(const vector<double>& values) {
    double sum = 0.0;
    int count = values.size();

    for (const double& value : values) {
        sum += value;
    }

    return sum / count;
}

void normalizeMinMax(int min, int max, int newMin, int newMax, vector<double>& values) {
    for (double& value : values) {
        value = ((value - min) / (max - min)) * (newMax - newMin) + newMin;
    }
}

void zScoreNormalize(vector<double>& values, double average) {
    double standardDeviation = 0.0;

    for (const double& value : values) {
        standardDeviation += pow(value - average, 2);
    }

    standardDeviation = sqrt(standardDeviation / values.size());

    for (double& value : values) {
        value = (value - average) / standardDeviation;
    }
}

int main() {
    ifstream inputFile("example.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    vector<double> data;
    double number = 0.0;

    while (inputFile >> number) {
        data.push_back(number);
    }

    vector<double> originalData = data;

    int newMin, newMax;
    cout << "Enter New Min: "; cin >> newMin;
    cout << "Enter New Max: "; cin >> newMax;

    int oldMin = findMinValue(data);
    int oldMax = findMaxValue(data);
    double average = calculateAverage(data);

    normalizeMinMax(oldMin, oldMax, newMin, newMax, data);

    cout << "New Min-Max Normalization Values:" << endl;
    for (const double& value : data) {
        cout << value << " ";
    }
    cout << endl;

    zScoreNormalize(originalData, average);

    cout << "Z-Score Normalization Values:" << endl;
    for (const double& value : originalData) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}