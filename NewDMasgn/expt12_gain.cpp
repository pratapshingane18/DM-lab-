#include <bits/stdc++.h>
using namespace std;
 
vector<string> sub_classes;
map<string, int> mainClass;
map<string, unordered_set<string>> dist_val;
map<string, int> dist_val_count;
map<string, map<string, int>> val_count;

double maxGain = DBL_MIN;
string root = "null";

ofstream fw;

void calculateGain(string subClass, double &mainC_gain)
{
    double totR = mainClass["Yes"] + mainClass["No"];
    double ent = 0;

    for (auto dv : dist_val[subClass])
    {
        double tR = dist_val_count[dv];
        double pR = val_count[dv]["Yes"], nR = val_count[dv]["No"];

        if (pR != 0)
            ent += -(tR / totR) * ((pR / tR) * log2(pR / tR));

        if (nR != 0)
            ent += -(tR / totR) * ((nR / tR) * log2(nR / tR));
    }

    cout << fixed << setprecision(4); // Set output to fixed-point notation with 4 decimal places

    cout << "Expected_Info ( " << subClass << "|playGame ) = " << ent << "\n";
    fw << "Expected_Info ( " << subClass << "|playGame )," << ent << "\n";

    double gain = mainC_gain - ent;
    cout << "Information_Gain ( " << subClass << "|playGame ) = " << gain << "\n\n";
    fw << "Information_Gain ( " << subClass << "|playGame )," << gain << "\n";

    if (gain > maxGain)
    {
        maxGain = gain;
        root = subClass;
    }
}

int main()
{
    fstream file("expt12_ip_gain.csv", ios::in);

    string line, word;
    string day, outlook, temp, humidity, wind, playGame;

    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }

    int j = 0;
    string main_class = "playgame";

    while (getline(file, line))
    {
        stringstream str(line);

        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playGame, ',');

        if (j == 0)
        {
            j++;
            continue;
        }

        dist_val["Outlook"].insert(outlook);
        dist_val["Temp"].insert(temp);
        dist_val["Humidity"].insert(humidity);
        dist_val["Wind"].insert(wind);

        mainClass[playGame]++;

        dist_val_count[outlook]++;
        dist_val_count[temp]++;
        dist_val_count[humidity]++;
        dist_val_count[wind]++;

        val_count[outlook][playGame]++;
        val_count[temp][playGame]++;
        val_count[humidity][playGame]++;
        val_count[wind][playGame]++;
    }

    double posR = mainClass["Yes"], negR = mainClass["No"];
    double totR = posR + negR;

    double mainC_gain = -((posR / totR) * log2(posR / totR) + (negR / totR) * log2(negR / totR));

    cout << "Main Class Entropy : " << mainC_gain << "\n";

    fw.open("exp12_op_gain.csv", ios::out); // Open the output file

    calculateGain("Outlook", mainC_gain);
    calculateGain("Temp", mainC_gain);
    calculateGain("Humidity", mainC_gain);
    calculateGain("Wind", mainC_gain);

    cout << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";
    fw << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";

    fw.close(); // Close the output file

    return 0;
}
