#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <limits.h>
#include <assert.h>
using namespace std;

struct Data {
	vector<double> feature;
	int cluster;
};

class Kmeans{
    private:
        int featureNum;
        int clusterNum;
        int recordNum;
        int maxIterNum;
        double endError;
        vector<Data> dataSet;
        double** means;
        double CalcDistance(vector<double>& d1, double* d2);
        bool CompareMeans(double** nextMeans);

    public:
        Kmeans(vector<Data>& dataSet, int featureNum, int clusterNum);
        ~Kmeans();
        void init(double endError, int maxIterNum);
        void cluster();
        double predict(vector<double>& feature, int& cluster);
};

Kmeans::~Kmeans()
{
    for(int i = 0; i < clusterNum; i++)
        delete[] means[i];
    delete means;
}

Kmeans::Kmeans(vector<Data>& dataSet, int featureNum, int clusterNum)
{
    this->dataSet = dataSet;
    this->featureNum = featureNum;
    this->clusterNum = clusterNum;
    this->recordNum = dataSet.size();
    init(0e-5, 100);
}

void Kmeans::init(double endError, int maxIterNum)
{
    this->endError = endError;
    this->maxIterNum = maxIterNum;
    int interval = recordNum/clusterNum;
    means = new double*[clusterNum];
    for(int i = 0; i < clusterNum; i++){
        means[i] = new double[featureNum];
        int idx = interval * i + (interval - 1) * rand() / RAND_MAX;
        Data data = dataSet[idx];
        for(int j = 0; j < featureNum; j++)
            means[i][j] = data.feature[j];
    }
}

double Kmeans::CalcDistance(vector<double>& d1, double* d2)
{
    double distance = 0.0;
    for(int i = 0; i < featureNum; i++)
        distance += (d1[i]-d2[i]) * (d1[i]-d2[i]);
    distance = sqrt(distance);
    return distance;
}

bool Kmeans::CompareMeans(double** nextMeans)
{
    for(int i = 0; i < clusterNum; i++){
        for(int j = 0; j < featureNum; j++)
            if(abs(means[i][j] - nextMeans[i][j]) > endError)
                return false;
    }
    return true;
}

double Kmeans::predict(vector<double>& feature, int& cluster)
{
    int minDist = -1;
    for(int j = 0; j < clusterNum; j++){
        double dis = CalcDistance(feature, means[j]);
        if(minDist > dis || minDist == -1){
            cluster = j;
            minDist = dis;
        }
    }
    return minDist;
}

void Kmeans::cluster()
{
    int iter = 0;
    assert(recordNum > clusterNum);

    int* num = new int[clusterNum];
    double** nextMeans = new double*[clusterNum];
    for(int i = 0; i < clusterNum; i++)
        nextMeans[i] = new double[featureNum];

    while(iter < maxIterNum)
    {
        for(int i = 0; i < clusterNum; i++)
            memset(nextMeans[i], 0, sizeof(double)*featureNum);
        memset(num, 0, sizeof(int)*clusterNum);

        //计算每一个点到中心点的距离，并把该点赋到最近的中心点
        double curCost = 0.0;
        for(int i = 0; i < recordNum; i++)
        {
            double minDist = predict(dataSet[i].feature, dataSet[i].cluster);
            curCost += minDist;
            num[dataSet[i].cluster]++;
            for(int d = 0; d < featureNum; d++)
                nextMeans[dataSet[i].cluster][d] += dataSet[i].feature[d];
        }
        curCost /= recordNum;

        //重新计算中心点,求平均
        for(int k = 0; k < clusterNum; k++){
            if(num[k] > 0){
                for(int d = 0; d < featureNum; d++)
                    nextMeans[k][d] /= num[k];
            }
        }

        if(CompareMeans(nextMeans))
            break;

        for(int i = 0; i < clusterNum; i++)
            memcpy(means[i], nextMeans[i], sizeof(double)*featureNum);

        iter++;
    }

    for(int i = 0; i < clusterNum; i++)
        delete[] nextMeans[i];
    delete[] nextMeans;
    delete[] num;
}

int main()
{


}
