// Include necessary header for input and output operations
#include <bits/stdc++.h>
using namespace std;

// Function to perform binning of data based on mean
void binDataByMean(vector<int> &data, int numBins)
{
    // Calculate the number of data points
    int len = data.size();

    // Calculate the size of each bin
    int binsize = len / numBins;
    int ite = 0, sum = 0;

    // Vector to store binned data
    vector<int> binnedData;

    // Iterate through the data points
    for (int i = 0; i < len; i++)
    {
        // Calculate the sum for each bin
        sum += data[i];

        // Check if a bin is complete
        if (i && !((i + 1) % binsize) && i <= (numBins * binsize))
        {
            // Calculate the mean for the current bin
            sum = sum / binsize;

            // Add the mean to the binned data for the bin size
            for (int j = 0; j < binsize; j++)
            {
                binnedData.push_back(sum);
            }

            // Reset the sum for the next bin
            sum = 0;
        }
    }

    // Temporary variables for bin size and bin count
    int temp = binsize;
    int binctn = 1;

    // Display the binned data
    cout << "Bin 1: " << endl;
    for (int i = 0; i < len; i++)
    {
        // Check if a new bin is starting
        if (i && !((i) % binsize) && i < binnedData.size())
        {
            binctn++;
            cout << "Bin " << binctn << ": " << endl;
        }

        // Display the binned data or the original data if binned data is not available
        if (i < binnedData.size())
            cout << binnedData[i] << " ";
        else
            cout << data[i] << " ";
        
        cout << endl;
    }
    cout << endl;
}

// Main function
int main()
{
    // Vector to store input data
    vector<int> data;

    // Variable to store the number of bins
    int numBins;

    // Prompt user to enter the number of bins
    cout << "Enter Number of Bins: ";
    cin >> numBins;

    // Read data from CSV file
    ifstream inputFile("exp_3_ip.csv");
    if (inputFile.is_open())
    {
        // Read each line from the file and convert it to an integer, then store in the data vector
        string line;
        while (getline(inputFile, line))
        {
            int value = stoi(line);
            data.push_back(value);
        }
        inputFile.close();
    }
    else
    {
        // Display an error message if the file cannot be opened
        cerr << "Unable to open file" << endl;
        return 1;
    }

    // Sort the data vector
    sort(data.begin(), data.end());

    // Perform binning based on mean
    binDataByMean(data, numBins);

    return 0;
}
