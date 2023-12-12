#include <bits/stdc++.h>

using namespace std;

// Function to read data from a CSV file for 3D data (x, y, z)
vector<vector<double>> readDataFromCSV(const string &filename)
{
    vector<vector<double>> data;
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
            vector<double> row;

            while (getline(rowStream, value, ','))
            {
                try
                {
                    row.push_back(stod(value));
                }
                catch (std::invalid_argument &e)
                {
                }
            }

            // Check if the row has three values (x, y, z)
            if (row.size() == 3)
            {
                data.push_back(row);
            }
            else
            {
                cerr << "Error: Each row should have three values (x, y, z)." << endl;
                data.clear(); // Clear the data if there's an error
                break;
            }
        }
    }

    file.close();
    return data;
}

// Function to calculate the Pearson correlation coefficient for 3D data
double calculateCorrelationCoefficient(const vector<vector<double>> &data)
{
    if (data.empty())
    {
        cerr << "Error: Empty data set for correlation calculation." << endl;
        return 0.0;
    }

    size_t n = data.size();

    double sumX = 0.0, sumY = 0.0, sumZ = 0.0;
    double sumXY = 0.0, sumXZ = 0.0, sumYZ = 0.0;
    double sumX2 = 0.0, sumY2 = 0.0, sumZ2 = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        double x = data[i][0];
        double y = data[i][1];
        double z = data[i][2];

        sumX += x;
        sumY += y;
        sumZ += z;
        sumXY += x * y;
        sumXZ += x * z;
        sumYZ += y * z;
        sumX2 += x * x;
        sumY2 += y * y;
        sumZ2 += z * z;
    }

    // Calculate means
    double meanX = sumX / n;
    double meanY = sumY / n;
    double meanZ = sumZ / n;

    // Calculate the correlation coefficient
    double numerator = n * (sumXY - sumX * meanY - sumY * meanX) +
                       sumX * sumY * meanZ + sumXZ * meanY + sumYZ * meanX -
                       n * sumX * meanY * meanZ - n * sumY * meanX * meanZ - n * sumZ * meanX * meanY;

    double denominatorX = n * sumX2 - sumX * sumX;
    double denominatorY = n * sumY2 - sumY * sumY;
    double denominatorZ = n * sumZ2 - sumZ * sumZ;

    double denominator = sqrt(denominatorX * denominatorY * denominatorZ);

    double correlation = numerator / denominator;

    return correlation;
}

int main()
{
    // Read 3D data from input.csv
    vector<vector<double>> allData = readDataFromCSV("exp3D.csv");

    if (allData.empty())
    {
        return 1; // Exit if there was an error reading the data
    }

    // Calculate the Pearson correlation coefficient for 3D data
    double correlation = calculateCorrelationCoefficient(allData);

    // Output the correlation coefficient
    cout << "Correlation Coefficient: " << correlation << endl;

    return 0;
}
