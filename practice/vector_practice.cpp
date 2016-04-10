#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    int featureNum = 2;
    int clusterNum = 2;
    vector<vector<double>> data;
    for(int i = 0; i < clusterNum; i++){
        vector<double> d(featureNum,0);
        data.push_back(d);
    }

    vector<vector<double>> data3({{2.0,3,0},{4.0,5.0}});
    data = data3;


    double** data2 = new double*[clusterNum];
    for(int i = 0; i < clusterNum; i++){
        data2[i] = new double[featureNum];
        memset(data2[i], 0, sizeof(double)*featureNum);
    }

    for(int i = 0; i < clusterNum; i++){
        for(int j = 0; j < featureNum; j++)
            cout<<data[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    for(int i = 0; i < clusterNum; i++)
        delete[] data2[i];
    delete[] data2;


}
