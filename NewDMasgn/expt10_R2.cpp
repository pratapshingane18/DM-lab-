#include <bits/stdc++.h>
using namespace std;

int main() {

    vector<vector<float>> arr;

    ifstream file("expt10_R2_input.csv"); 
    if (!file.is_open()) {
        cerr << "Error in opening input file." << endl;
        return 1;
    }
    string line;
    int n = 0;
    while (getline(file, line)) {
        n++; 
        istringstream iss(line);
        string x, y, countStr;
        getline(getline(iss, x, ','), y, ',');
        float x_cor = stof(x);
        float y_cor = stof(y);
        arr.push_back({x_cor, y_cor});
    }
    
    int myit = 3;
    cout << "enter number of clusters: ";
    int k;  cin >> k;
    cout << endl;
    vector<vector<float>> c;
    for (int i=0; i<k; i++) c.push_back(arr[i]);
    while (myit--) {
        vector<vector<float>> points[k];
        cout << "Iteration " << 3-myit << endl;
        for (int i=0; i<n; i++) {
            float mindist = INT_MAX;
            int min_cluster = 0;
            cout << "Point: " << arr[i][0] << ", " << arr[i][1] << endl;
            for (int j=0; j<k; j++) {
                float x =pow(arr[i][0] - c[j][0], 2);
                float y =pow(arr[i][1] - c[j][1], 2);
                float distance = sqrt(x+y);
                if (distance<mindist) {
                    mindist = distance;
                    min_cluster = j;
                }
                cout << "Distance from cluster " << j << " is " << distance << endl;
            }
            points[min_cluster].push_back(arr[i]);
            cout << "Point " << arr[i][0] << ", " << arr[i][1] << " belongs to cluster" << min_cluster << " " << c[min_cluster][0] << ", " << c[min_cluster][1] << endl << endl;
        }

        for (int i=0; i<k; i++) {
            float x = 0;
            float y = 0;
            for (int j=0; j<points[i].size(); j++) {
                x += points[i][j][0];
                y += points[i][j][1];
            }
            if (points[i].size() > 0) {
                x = x/points[i].size();
                y = y/points[i].size();
            }
            c[i][0] = x;
            c[i][1] = y;
            cout << "New centroid of cluster" << i << " is " << x << ", " << y << endl;
        }
        cout << endl << endl;
    }
    cout << "Final clusters: " << endl;
    for (int i=0; i<k; i++) {
        cout << "Cluster " << i << endl;
        cout << c[i][0] << ", " << c[i][1] << endl << endl;
    }

    return 0;
}