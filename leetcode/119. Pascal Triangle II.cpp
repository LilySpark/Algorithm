#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row;

        if(rowIndex == 0)
            row.push_back(1);
        else if(rowIndex==1)
        {
            row.push_back(1);
            row.push_back(1);
        }
        else
        {
            row.push_back(1);
            row.push_back(1);
            vector<int>::iterator iter;
            for(int j = 2; j <= rowIndex; j++){
                iter = row.begin()+1;
                row.insert(iter,row[0] + row[1]);
                for(int i = 2; i < j; i++)
                    row[i]=row[i] + row[i+1];
            }
        }
        return row;
    }
};

int main()
{
    Solution s;
    vector<int> rows =  s.getRow(3);
    for(int i = 0; i < rows.size(); i++)
        cout<<rows[i]<<" ";
    cout<<endl;

    return 0;
}
