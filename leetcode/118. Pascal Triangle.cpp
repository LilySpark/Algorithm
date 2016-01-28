#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> rows;
        vector<int> end{1};

        if(numRows > 0)
        {
            rows.push_back(end);
            for(int j = 1; j < numRows; j++){
                vector<int> row;
                row.push_back(1);
                for(int i = 1; i < j; i++)
                    row.push_back(rows[j-1][i-1] + rows[j-1][i]);
                row.push_back(1);
                rows.push_back(row);
            }
        }
        return rows;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> rows =  s.generate(3);
    for(int i = 0; i < rows.size(); i++){
        for(int j=0; j < rows[i].size();j++)
            cout<<rows[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
