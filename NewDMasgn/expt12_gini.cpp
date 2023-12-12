#include <bits/stdc++.h>
using namespace std;

float calculateGini(string Class, vector<map<string, string>> data)
{
    float totalRecords = data.size();
    float giniIndex = 0.0;

    unordered_set<string> uniqueValues;

    for (const auto &row : data)
    {
        uniqueValues.insert(row.at(Class));
    }

    for (const auto &value : uniqueValues)
    {
        float tempGini=0;
        float count = 0;
        float TennisCnt=0,CinemaCnt=0;

        for (const auto &row : data)
        {
            if (row.at(Class) == value)
            {
                count += 1;
                if (row.at("Decision")=="Tennis")
                TennisCnt++;
                else CinemaCnt++;
            }
        }

        // cout<<value<<" Tennis: "<<TennisCnt<<" Cinema: "<<CinemaCnt<<endl;
        // cout<<value<<" "<<count<<endl;
        
        float prob_yes = TennisCnt / count;
        float prob_no = CinemaCnt / count;
        tempGini = ((float)1-(float)(prob_yes*prob_yes)-(float)(prob_no*prob_no));
        // cout<<value<< "=> 1- vala formula "<<tempGini<<endl;
        tempGini= tempGini * (count/totalRecords);
        // cout<<value<<" "<<tempGini<<endl;
        giniIndex+=tempGini;

    }
    
    return giniIndex;
}

int main()
{
    vector<map<string, string>> data;
    ifstream file("expt12_ip_gini.csv");

    if (!file.is_open())
    {
        printf("Error in opening input file : ");
        return -1;
    }
    string line, word;
    string weekend, weather, parents, money, decision;

    int j = 0;
    while (getline(file, line))
    {
        stringstream str(line);

        getline(str, weekend, ',');
        getline(str, weather, ',');
        getline(str, parents, ',');
        getline(str, money, ',');
        getline(str, decision, ',');

        if (j == 0)
        {
            j++;
            continue;
        }
        map<string, string> row;
        row["Weekend"] = weekend;
        row["Weather"] = weather;
        row["Parents"] = parents;
        row["Money"] = money;
        row["Decision"] = decision;

        data.push_back(row);
    }
    file.close();

    string mainClass = "Decision";
    // float giniMainClass = calculateGini(mainClass, data);
    // cout << "Main Class Gini Index: "<<setprecision(5) << giniMainClass << endl;
    int mini = INT_MAX;
    string subclassMax = "";

    for (const auto &subClass : data[0])
    {
        if (subClass.first != mainClass)
        {
            float giniSubClass = calculateGini(subClass.first, data);
            cout << "Gini Index for " << subClass.first << ": " << setprecision(5) << giniSubClass << endl;

            if (giniSubClass < mini)
            {
                mini = giniSubClass;
                subclassMax = subClass.first;
            }
        }
    }
    cout << "Subclass : " << subclassMax << " has minimum gini index. Hence it will be selected as root for splitting";
    return 0;
}
