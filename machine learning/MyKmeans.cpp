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

class Kmeans{
    private:
        int featureNum;
        int clusterNum;
        int recordNum;
        int maxIterNum;
        double endError;
        vector<vector<double>> dataSet;
        vector<int> cluster;
        vector<vector<double>> means;
        double CalcDistance(vector<double>& d1, vector<double>& d2);
        bool CompareMeans(vector<vector<double>>& nextMeans);

    public:
        Kmeans(vector<vector<double>>& dataSet, int featureNum, int clusterNum);
        void init(double endError, int maxIterNum);
        void KmeansCluster();
        double predict(vector<double>& feature, int& cluster);
};

Kmeans::Kmeans(vector<vector<double>>& dataSet, int featureNum, int clusterNum)
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
    for(int i = 0; i < clusterNum; i++){
        int idx = interval * i + (interval - 1) * rand() / RAND_MAX;
        means.push_back(dataSet[idx]);
        cluster.push_back(-1);
    }
}

double Kmeans::CalcDistance(vector<double>& d1, vector<double>& d2)
{
    double distance = 0.0;
    for(int i = 0; i < featureNum; i++)
        distance += (d1[i]-d2[i]) * (d1[i]-d2[i]);
    distance = sqrt(distance);
    return distance;
}

bool Kmeans::CompareMeans(vector<vector<double>>& nextMeans)
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

void Kmeans::KmeansCluster()
{
    int iter = 0;
    assert(recordNum > clusterNum);
    while(iter < maxIterNum)
    {
        vector<vector<double>> nextMeans;
        for(int i = 0; i < clusterNum; i++){
            vector<double> d(featureNum,0.0);
            nextMeans.push_back(d);
        }
        vector<int> num(clusterNum, 0);

        //计算每一个点到中心点的距离，并把该点赋到最近的中心点
        double curCost = 0.0;
        for(int i = 0; i < recordNum; i++)
        {
            double minDist = predict(dataSet[i], cluster[i]);
            curCost += minDist;
            num[cluster[i]]++;
            for(int d = 0; d < featureNum; d++)
                nextMeans[cluster[i]][d] += dataSet[i][d];
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
        means = nextMeans;
        iter++;
    }
}

void read(const char* infile, vector<vector<double>>& dataSet)
{
    FILE *fin = fopen(infile, "r");
    int recordNum, featureNum;
	fscanf(fin, "%d%d", &recordNum, &featureNum);
	for(int i = 0; i < recordNum; i++)
	{
	    double feature;
	    vector<double> d;
	    for(int j = 0; j < featureNum; j++)
        {
            fscanf(fin, "%f", &feature);
            d.push_back(feature);
        }
        dataSet.push_back(d);
	}
	fclose(fin);
}

int main()
{


}
