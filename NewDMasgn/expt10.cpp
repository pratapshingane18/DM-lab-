//expt 10=>k means clustering
#include <bits/stdc++.h>
using namespace std;

float distance(float x1, float y1, float x2, float y2)
{
    // cout << "\ndistance func " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    return sqrt(((float)x2 - x1) * ((float)x2 - x1) + ((float)y2 - y1) * ((float)y2 - y1));
}

void updateCentre(pair<float, float> &C, pair<float, float> &temp)
{
    C.first = (C.first + temp.first) / 2;
    C.second = (C.second + temp.second) / 2;
}

int main()
{

    string line;
    string point, x, y;
    int i = 0;
    int val1;
    int val2;
    vector<pair<int, int>> v;
    fstream in("expt10_input.csv", ios::in);
    if (!in.is_open())
    {
        cout << "couldn't open file";
        return -1;
    }
    while (getline(in, line))
    {
        stringstream str(line);
        if (i == 0)
        {
            i++;
            continue;
        }
        getline(str, point, ',');
        getline(str, x, ',');
        getline(str, y, ',');
        val1 = stoi(x);
        val2 = stoi(y);

        v.push_back({val1, val2});
    }
    int n = v.size();
    pair<float, float> c1, c2;
    c1 = v[0];
    c2 = v[n - 1];
    //ofstream out("op.csv");

    vector<vector<float>> distVec(2, vector<float>(n));
    int k = 0;
    pair<float, float> min1, min2;
    float mini = INT_MAX;
    for (int i = 0; i < v.size(); i++)
    {

        int f_x1 = c1.first;
        int s_y1 = c1.second;
        int f_x2 = v[i].first;
        int s_y2 = v[i].second;

        if (f_x1 == f_x2 && s_y1 == s_y2)
        {
            distVec[0][k] = 0;
            k++;
        }
        else
        {
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            if (dis < mini)
            {
                min1.first = f_x2;
                min1.second = s_y2;
            }
            distVec[0][k] = dis;
            k++;
        }
    }

    updateCentre(c1, min1);

    mini = INT_MAX;
    k = 0;
    for (int i = 0; i < v.size(); i++)
    {

        int f_x1 = c2.first;
        int s_y1 = c2.second;
        int f_x2 = v[i].first;
        int s_y2 = v[i].second;
        // cout << f_x2 << " " << s_y2 << endl;
        if (f_x1 == f_x2 && s_y1 == s_y2)
        {

            distVec[1][k] = 0;
            k++;
        }
        else
        {
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            if (dis < mini)
            {
                min2.first = f_x2;
                min2.second = s_y2;
            }
            distVec[1][k] = dis;
            k++;
        }
    }

    updateCentre(c2, min2);
    for (int i = 0; i < distVec.size(); i++)
    {
        cout << "Distances from C" << i + 1 << " " << endl;
        for (int j = 0; j < n; j++)
        {
            cout << distVec[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // cout << c1.first << " " << c1.second << " " << c2.first << " " << c2.second << endl;

    k = 0;
    // mini = INT_MAX;
    for (int i = 0; i < v.size(); i++)
    {

        int f_x1 = c1.first;
        int s_y1 = c1.second;
        int f_x2 = v[i].first;
        int s_y2 = v[i].second;

        if (f_x1 == f_x2 && s_y1 == s_y2)
        {

            distVec[0][k] = 0;
            k++;
        }
        else
        {
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            distVec[0][k] = dis;
            k++;
        }
    }

    k = 0;
    for (int i = 0; i < v.size(); i++)
    {

        int f_x1 = c2.first;
        int s_y1 = c2.second;
        int f_x2 = v[i].first;
        int s_y2 = v[i].second;

        if (f_x1 == f_x2 && s_y1 == s_y2)
        {

            distVec[1][k] = 0;
            k++;
        }
        else
        {
            float dis = distance(f_x1, s_y1, f_x2, s_y2);

            distVec[1][k] = dis;
            k++;
        }
    }

    vector<int> cluster1, cluster2;
    for (int i = 0; i < n; i++)
    {
        if (distVec[0][i] <= distVec[1][i])
            cluster1.push_back(i + 1);
        else
            cluster2.push_back(i + 1);
    }

    for (int i = 0; i < distVec.size(); i++)
    {
        cout << "Distances from C" << i + 1 << " " << endl;
        for (int j = 0; j < n; j++)
        {
            cout << distVec[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Cluster1: ";
    for (int i = 0; i < cluster1.size(); i++)
    {
        cout << cluster1[i] << " ";
    }
    cout << endl;

    cout << "Cluster2: ";
    for (int i = 0; i < cluster2.size(); i++)
    {
        cout << cluster2[i] << " ";
    }

    return 0;
}