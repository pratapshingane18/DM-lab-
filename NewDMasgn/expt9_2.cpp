#include <bits/stdc++.h>

using namespace std;

// Function to read data from a CSV file
vector<double> readDataFromCSV(const string &filename)
{
    vector<double> data;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cerr << "Error opening the file: " << filename << endl;
        return data;
    }

    while (getline(file, line))
    {
        if (!line.empty())
        {
            istringstream rowStream(line);
            string value;

            while (getline(rowStream, value, ','))
            {
                try
                {
                    data.push_back(stod(value));
                }
                catch (std::invalid_argument &e)
                {
                }
            }
        }
    }

    file.close();
    return data;
}

// Function to calculate the Pearson correlation coefficient
double calculateCorrelationCoefficient(const vector<double> &data1, const vector<double> &data2)
{
    if (data1.size() != data2.size())
    {
        cerr << "Data sets must have the same number of elements for correlation calculation." << endl;
        return 0.0;
    }

    double sumX = 0.0;
    double sumY = 0.0;
    double sumXY = 0.0;
    double sumX2 = 0.0;
    double sumY2 = 0.0;

    for (size_t i = 0; i < data1.size(); i++)
    {
        double x = data1[i];
        double y = data2[i];

        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
        sumY2 += y * y;
    }

    double n = static_cast<double>(data1.size());

    // Calculate the means
    double meanX = sumX / n;
    double meanY = sumY / n;

    // Calculate the correlation coefficient
    double correlation = (n * sumXY - sumX * sumY) / sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

    return correlation;
}

int main()
{
    // Read data from input.csv
    vector<double> allData = readDataFromCSV("expt9_input.csv");

    if (allData.size() % 2 != 0)
    {
        cerr << "Error: The number of elements in the file is not even (expected two columns)." << endl;
        return 1;
    }

    // Separate the data into two vectors
    vector<double> data1, data2;
    for (size_t i = 0; i < allData.size(); i += 2)
    {
        data1.push_back(allData[i]);
        data2.push_back(allData[i + 1]);
    }

    // Calculate the Pearson correlation coefficient
    double correlation = calculateCorrelationCoefficient(data1, data2);

    // Output the correlation coefficient
    cout << "Correlation Coefficient: " << correlation << endl;

    return 0;
}